/*
 *      application-controller.vala
 *      Copyright (C) 2010 Canonical Ltd
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 *
 *
 *      Authored by Gordon Allott <gord.allott@canonical.com>
 */

namespace Unity.Launcher
{
  public errordomain AppTypeError {
    NO_DESKTOP_FILE
  }

  public class ApplicationController : ScrollerChildController
  {
    public string desktop_file { get; private set; }

    private KeyFile desktop_keyfile;
    private string icon_name;
    private Bamf.Application? app = null;
    private Dbusmenu.Client menu_client;
    private Dbusmenu.Menuitem cached_menu;
    private int menu_items_realized_counter;
    private string _fav_id = "";
    public string fav_id {
      get
        {
          if (_fav_id == "" || _fav_id == null &&
              desktop_file != "" && desktop_file != null)
            {
              var filepath = Path.get_basename (desktop_file);
              _fav_id = "app-" + filepath;
            }
          return _fav_id;
        }
      set { _fav_id = value; }
    }

    public bool is_favorite = false;

    public ApplicationController (string? desktop_file_, ScrollerChild child_)
    {
      Object (child: child_);

      if (desktop_file_ != null)
        {
          desktop_file = desktop_file_;
          load_desktop_file_info ();
        }
    }

    ~ApplicationController ()
    {
    }

    construct
    {
      var favorites = Unity.Favorites.get_default ();
      favorites.favorite_added.connect (on_favorite_added);
      favorites.favorite_removed.connect (on_favorite_removed);

      // we need to figure out if we are a favoritem

      is_favorite = is_sticky ();
      child.pin_type = PinType.UNPINNED;
      if (is_sticky ())
        child.pin_type = PinType.PINNED;
    }

    public override QuicklistController? get_menu_controller ()
    {
      QuicklistController new_menu = new ApplicationQuicklistController (this);
      return new_menu;
    }

    public new void closed ()
    {
      if (!is_sticky () && (app is Bamf.Application) == false)
        {
          request_removal ();
        }
    }

    public void set_sticky (bool is_sticky = true)
    {
      if (desktop_file == "" || desktop_file == null)
        return;

      var favorites = Unity.Favorites.get_default ();

      if (is_sticky)
        {
          favorites.set_string (fav_id, "type", "application");
          favorites.set_string (fav_id, "desktop_file", desktop_file);
          favorites.add_favorite (fav_id);
        }
      else
        {
          favorites.remove_favorite (fav_id);
        }
    }

    public bool is_sticky ()
    {
      if (desktop_file == "" || desktop_file == null)
        return false;

      var favorites = Unity.Favorites.get_default ();
      return favorites.is_favorite (fav_id);
    }

    public void close_windows ()
    {
      if (app is Bamf.Application)
        {
          Array<uint32> xids = app.get_xids ();
          Unity.global_shell.close_xids (xids);
        }
    }

    public void set_priority (float priority)
    {
      if (desktop_file == "" || desktop_file == null)
        return;

      var favorites = Unity.Favorites.get_default ();
      favorites.set_float (fav_id, "priority", priority);
    }

    public float get_priority () throws AppTypeError
    {
      if (desktop_file == "" || desktop_file == null)
        throw new AppTypeError.NO_DESKTOP_FILE("There is no desktop file for this app, can't get priority");

      var favorites = Unity.Favorites.get_default ();
      return favorites.get_float (fav_id, "priority");
    }

    private void on_favorite_added (string uid)
    {
      //check to see if we are the favorite
      if (uid == fav_id)
        {
          is_favorite = true;
          child.pin_type = PinType.PINNED;
        }
    }

    private void on_favorite_removed (string uid)
    {
      if (uid == fav_id)
        {
          is_favorite = false;
          child.pin_type = PinType.UNPINNED;
          closed ();
          if (".local" in desktop_file)
           FileUtils.remove (desktop_file);
        }
    }

    public override void get_menu_actions (ScrollerChildController.menu_cb callback)
    {

      // first check to see if we have a cached client, if we do, just re-use that
      // check for a menu from bamf
      if (app is Bamf.Application)
        {
          GLib.List<Bamf.View> views = app.get_children ();
          foreach (Bamf.View view in views)
            {
              if (view is Bamf.Indicator)
                {
                  string path = (view as Bamf.Indicator).get_dbus_menu_path ();
                  string remote_address = (view as Bamf.Indicator).get_remote_address ();

                  // Yes, right here, i have lambda's inside lambda's... shutup.
                  menu_client = new Dbusmenu.Client (remote_address, path);
                  menu_client.layout_updated.connect (() => {
                    var menu = menu_client.get_root ();
                    cached_menu = menu;
                    if (menu is Dbusmenu.Menuitem == false)
                      warning (@"Didn't get a menu for path: $path - address: $remote_address");

                    unowned GLib.List<Dbusmenu.Menuitem> menu_items = menu.get_children ();
                    menu_items_realized_counter = (int)menu_items.length ();
                    foreach (Dbusmenu.Menuitem menuitem in menu_items)
                    {
                      menuitem.realized.connect (() =>
                        {
                          menu_items_realized_counter -= 1;
                          if (menu_items_realized_counter < 1)
                            {
                              callback (menu);
                            }

                        });
                    }
                  });
                }
            }
        }


      if (desktop_file == "" || desktop_file == null)
        {
          callback (null);
        }

      // find our desktop shortcuts
      Indicator.DesktopShortcuts shortcuts = new Indicator.DesktopShortcuts (desktop_file, "Unity");
      unowned string [] nicks = shortcuts.get_nicks ();

      if (nicks.length < 1)
        callback (null);

      Dbusmenu.Menuitem root = new Dbusmenu.Menuitem ();
      root.set_root (true);

      foreach (string nick in nicks)
        {
          string local_nick = nick.dup ();
          unowned string name = shortcuts.nick_get_name (local_nick);
          string local_name = name.dup ();

          Dbusmenu.Menuitem shortcut_item = new Dbusmenu.Menuitem ();
          shortcut_item.property_set (Dbusmenu.MENUITEM_PROP_LABEL, local_name);
          shortcut_item.property_set_bool (Dbusmenu.MENUITEM_PROP_ENABLED, true);
          shortcut_item.property_set_bool (Dbusmenu.MENUITEM_PROP_VISIBLE, true);
          shortcut_item.item_activated.connect ((timestamp) => {
            shortcuts.nick_exec (local_nick);
          });
          root.child_append (shortcut_item);

        }
      callback (root);
    }


    public override void get_menu_navigation (ScrollerChildController.menu_cb callback)
    {

      // build a dbusmenu that represents our generic application handling items
      Dbusmenu.Menuitem root = new Dbusmenu.Menuitem ();
      root.set_root (true);

      if (desktop_file != null && desktop_file != "")
        {
          Dbusmenu.Menuitem pinning_item = new Dbusmenu.Menuitem ();
          if (app is Bamf.Application)
            {
              pinning_item.property_set (Dbusmenu.MENUITEM_PROP_LABEL, _("Keep in Launcher"));
              pinning_item.property_set (Dbusmenu.MENUITEM_PROP_TOGGLE_TYPE, Dbusmenu.MENUITEM_TOGGLE_CHECK);
              if (is_sticky ())
                {
                  pinning_item.property_set_int (Dbusmenu.MENUITEM_PROP_TOGGLE_STATE, Dbusmenu.MENUITEM_TOGGLE_STATE_CHECKED);
                }
              else
                {
                  pinning_item.property_set_int (Dbusmenu.MENUITEM_PROP_TOGGLE_STATE, Dbusmenu.MENUITEM_TOGGLE_STATE_UNCHECKED);
                }
            }
          else
            {
              pinning_item.property_set (Dbusmenu.MENUITEM_PROP_LABEL, _("Remove from launcher"));
            }

          pinning_item.property_set_bool (Dbusmenu.MENUITEM_PROP_ENABLED, true);
          pinning_item.property_set_bool (Dbusmenu.MENUITEM_PROP_VISIBLE, true);
          pinning_item.item_activated.connect ((timestamp) => {
            set_sticky (!is_sticky ());
          });

          root.child_append (pinning_item);
        }

      if (app is Bamf.Application)
        {
          Dbusmenu.Menuitem app_item = new Dbusmenu.Menuitem ();
          app_item.property_set (Dbusmenu.MENUITEM_PROP_LABEL, _("Quit"));
          app_item.property_set_bool (Dbusmenu.MENUITEM_PROP_ENABLED, true);
          app_item.property_set_bool (Dbusmenu.MENUITEM_PROP_VISIBLE, true);

          app_item.item_activated.connect ((timestamp) => {
            if (app is Bamf.Application)
              {
                Array<uint32> xids = app.get_xids ();
                Unity.global_shell.close_xids (xids);
              }
          });
          root.child_append (app_item);
        }

        callback (root);
    }

    private static int order_app_windows (void* a, void* b)
      requires (a is Bamf.Window)
      requires (b is Bamf.Window)
    {
      unowned Bamf.Window awin = a as Bamf.Window;
      unowned Bamf.Window bwin = b as Bamf.Window;
      bool aurgent = awin.is_urgent ();
      bool burgent = bwin.is_urgent ();

      /* Urgent overrides time */
      if (aurgent && !burgent)
        {
          return 1;
        }
      else if (!aurgent && burgent)
        {
          return -1;
        }
      else if (awin.last_active () > bwin.last_active ())
        {
          /* Positive when a > b */
          return 1;
        }
      else if (awin.last_active () < bwin.last_active ())
        {
          /* Negative when a < b */
          return -1;
        }
      else
        {
          return 0;
        }
    }


    private void launch_desktop_file ()
    {
      Gdk.AppLaunchContext context = new Gdk.AppLaunchContext ();
      try
        {
          var appinfo = new DesktopAppInfo.from_filename (desktop_file);
          context.set_screen (Gdk.Display.get_default ().get_default_screen ());
          context.set_timestamp (Gdk.CURRENT_TIME);

          appinfo.launch (null, context);
          child.activating = true;
          // timeout after eight seconds
          GLib.Timeout.add_seconds (8, on_launch_timeout);
        }
      catch (Error e)
        {
          warning (e.message);
        }
    }

    private bool app_has_visable_window ()
      requires (app is Bamf.Application)
    {
      foreach (Bamf.Window window in app.get_windows ())
        {
          if (window.user_visible ()) return true;
        }
      return false;
    }

    public override void activate ()
    {
      if (app is Bamf.Application)
        {
          if (app.is_active ())
            {
              /* We only want to do expose if the window was _actually_
               * active i.e. the dash wasn't showing.
               */
              if (global_shell.get_mode () == ShellMode.MINIMIZED)
                {
                  Array<uint32> xids = app.get_xids ();
                  global_shell.expose_xids (xids);
                }
            }
          else if (app.is_running () && app_has_visable_window ())
            {
              unowned List<Bamf.Window> windows = app.get_windows ();
              windows.sort ((CompareFunc)order_app_windows);
              Unity.global_shell.show_window (windows.nth_data (windows.length ()-1).get_xid ());
            }
          else
            {
              launch_desktop_file ();
            }
        }
      else
        {
          launch_desktop_file ();
        }
      global_shell.hide_unity ();
    }

    private bool on_launch_timeout ()
    {
      child.activating = false;
      return false;
    }
    public void attach_application (Bamf.Application application)
    {
      app = application;
      desktop_file = app.get_desktop_file ().dup ();
      child.running = app.is_running ();
      child.active = app.is_active ();
      child.activating = false;

      app.running_changed.connect (on_app_running_changed);
      app.active_changed.connect (on_app_active_changed);
      app.closed.connect (detach_application);
      app.urgent_changed.connect (on_app_urgant_changed);
      app.user_visible_changed.connect ((value) => {
        hide = !value;
      });
      name = app.get_name ();
      if (name == null || name == "")
        warning (@"Bamf returned null for app.get_name (): $desktop_file");

      icon_name = app.get_icon ();
      load_icon_from_icon_name (icon_name);
    }

    public void detach_application ()
    {
      app.running_changed.disconnect (on_app_running_changed);
      app.active_changed.disconnect (on_app_active_changed);
      app.urgent_changed.disconnect (on_app_urgant_changed);
      app.closed.disconnect (detach_application);
      app = null;
      child.running = false;
      child.active = false;
      child.needs_attention = false;
      closed ();
    }

    public bool debug_is_application_attached ()
    {
      return app != null;
    }

    private void on_app_running_changed (bool running)
    {
      child.running = running;
      if (!running)
        {
          detach_application ();
        }
    }

    private void on_app_active_changed (bool active)
    {
      child.active = active;
    }

    private void on_app_urgant_changed (bool urgancy)
    {
      child.needs_attention = urgancy;
    }

    private void load_desktop_file_info ()
    {
      try
        {
          desktop_keyfile = new KeyFile ();
          desktop_keyfile.load_from_file (desktop_file, KeyFileFlags.NONE);
        }
      catch (Error e)
        {
          warning ("could not load desktop file: %s", e.message);
        }

      try
        {
          icon_name = desktop_keyfile.get_string (KeyFileDesktop.GROUP, KeyFileDesktop.KEY_ICON);
          load_icon_from_icon_name (icon_name);
        }
      catch (Error e)
        {
          warning ("could not load icon name from desktop file: %s", e.message);
        }

      try
        {
          name = desktop_keyfile.get_locale_string (KeyFileDesktop.GROUP, KeyFileDesktop.KEY_NAME);
        }
      catch (Error e)
        {
          warning ("could not load name from desktop file: %s", e.message);
        }

      try
        {
          name = desktop_keyfile.get_locale_string (KeyFileDesktop.GROUP, "X-GNOME-FullName");
        }
      catch (Error e)
        {
        }
    }
  }
}
