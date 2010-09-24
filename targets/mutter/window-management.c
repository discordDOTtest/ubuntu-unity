/* window-management.c generated by valac 0.10.0, the Vala compiler
 * generated from window-management.vala, do not modify */

/*
 * Copyright (C) 2009 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by Neil Jagdish Patel <neil.patel@canonical.com>
 *
 */

#include <glib.h>
#include <glib-object.h>
#include <mutter-plugins.h>
#include <stdlib.h>
#include <string.h>
#include <clutter/clutter.h>
#include <float.h>
#include <math.h>


#define UNITY_TYPE_WINDOW_MANAGEMENT (unity_window_management_get_type ())
#define UNITY_WINDOW_MANAGEMENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), UNITY_TYPE_WINDOW_MANAGEMENT, UnityWindowManagement))
#define UNITY_WINDOW_MANAGEMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), UNITY_TYPE_WINDOW_MANAGEMENT, UnityWindowManagementClass))
#define UNITY_IS_WINDOW_MANAGEMENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), UNITY_TYPE_WINDOW_MANAGEMENT))
#define UNITY_IS_WINDOW_MANAGEMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), UNITY_TYPE_WINDOW_MANAGEMENT))
#define UNITY_WINDOW_MANAGEMENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), UNITY_TYPE_WINDOW_MANAGEMENT, UnityWindowManagementClass))

typedef struct _UnityWindowManagement UnityWindowManagement;
typedef struct _UnityWindowManagementClass UnityWindowManagementClass;
typedef struct _UnityWindowManagementPrivate UnityWindowManagementPrivate;

#define UNITY_TYPE_PLUGIN (unity_plugin_get_type ())
#define UNITY_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), UNITY_TYPE_PLUGIN, UnityPlugin))
#define UNITY_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), UNITY_TYPE_PLUGIN, UnityPluginClass))
#define UNITY_IS_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), UNITY_TYPE_PLUGIN))
#define UNITY_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), UNITY_TYPE_PLUGIN))
#define UNITY_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), UNITY_TYPE_PLUGIN, UnityPluginClass))

typedef struct _UnityPlugin UnityPlugin;
typedef struct _UnityPluginClass UnityPluginClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define UNITY_TYPE_EXPOSE_MANAGER (unity_expose_manager_get_type ())
#define UNITY_EXPOSE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), UNITY_TYPE_EXPOSE_MANAGER, UnityExposeManager))
#define UNITY_EXPOSE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), UNITY_TYPE_EXPOSE_MANAGER, UnityExposeManagerClass))
#define UNITY_IS_EXPOSE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), UNITY_TYPE_EXPOSE_MANAGER))
#define UNITY_IS_EXPOSE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), UNITY_TYPE_EXPOSE_MANAGER))
#define UNITY_EXPOSE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), UNITY_TYPE_EXPOSE_MANAGER, UnityExposeManagerClass))

typedef struct _UnityExposeManager UnityExposeManager;
typedef struct _UnityExposeManagerClass UnityExposeManagerClass;

struct _UnityWindowManagement {
	GObject parent_instance;
	UnityWindowManagementPrivate * priv;
};

struct _UnityWindowManagementClass {
	GObjectClass parent_class;
};

struct _UnityWindowManagementPrivate {
	UnityPlugin* plugin;
	MutterWindow* last_mapped;
};


extern char* unity_maximus_user_unmaximize_hint;
static gpointer unity_window_management_parent_class = NULL;

GType unity_window_management_get_type (void) G_GNUC_CONST;
GType unity_plugin_get_type (void) G_GNUC_CONST;
#define UNITY_WINDOW_MANAGEMENT_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), UNITY_TYPE_WINDOW_MANAGEMENT, UnityWindowManagementPrivate))
enum  {
	UNITY_WINDOW_MANAGEMENT_DUMMY_PROPERTY
};
UnityWindowManagement* unity_window_management_new (UnityPlugin* p);
UnityWindowManagement* unity_window_management_construct (GType object_type, UnityPlugin* p);
static void unity_window_management_window_minimized (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window);
static void _unity_window_management_window_minimized_unity_plugin_window_minimized (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self);
static void unity_window_management_window_maximized (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height);
static void _unity_window_management_window_maximized_unity_plugin_window_maximized (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height, gpointer self);
static void unity_window_management_window_unmaximized (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height);
static void _unity_window_management_window_unmaximized_unity_plugin_window_unmaximized (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height, gpointer self);
static void unity_window_management_window_mapped (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window);
static void _unity_window_management_window_mapped_unity_plugin_window_mapped (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self);
static void unity_window_management_window_destroyed (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window);
static void _unity_window_management_window_destroyed_unity_plugin_window_destroyed (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self);
static void unity_window_management_kill_window_effects (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window);
static void _unity_window_management_kill_window_effects_unity_plugin_kill_window_effects (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self);
static gint unity_window_management_get_animation_speed (UnityWindowManagement* self, MutterWindow* window);
MutterPlugin* unity_plugin_get_plugin (UnityPlugin* self);
static void unity_window_management_window_minimized_completed (UnityWindowManagement* self, ClutterAnimation* anim);
static void _unity_window_management_window_minimized_completed_clutter_animation_completed (ClutterAnimation* _sender, gpointer self);
static gboolean unity_window_management_force_activate (UnityWindowManagement* self);
GType unity_expose_manager_get_type (void) G_GNUC_CONST;
UnityExposeManager* unity_plugin_get_expose_manager (UnityPlugin* self);
gboolean unity_expose_manager_get_expose_showing (UnityExposeManager* self);
static gboolean _unity_window_management_force_activate_gsource_func (gpointer self);
static void unity_window_management_window_mapped_completed (UnityWindowManagement* self, ClutterAnimation* anim);
static void _unity_window_management_window_mapped_completed_clutter_animation_completed (ClutterAnimation* _sender, gpointer self);
static void unity_window_management_window_destroyed_completed (UnityWindowManagement* self, ClutterAnimation* anim);
static void _unity_window_management_window_destroyed_completed_clutter_animation_completed (ClutterAnimation* _sender, gpointer self);
static GObject * unity_window_management_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void unity_window_management_finalize (GObject* obj);



static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _unity_window_management_window_minimized_unity_plugin_window_minimized (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self) {
	unity_window_management_window_minimized (self, plugin, window);
}


static void _unity_window_management_window_maximized_unity_plugin_window_maximized (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height, gpointer self) {
	unity_window_management_window_maximized (self, plugin, window, x, y, width, height);
}


static void _unity_window_management_window_unmaximized_unity_plugin_window_unmaximized (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height, gpointer self) {
	unity_window_management_window_unmaximized (self, plugin, window, x, y, width, height);
}


static void _unity_window_management_window_mapped_unity_plugin_window_mapped (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self) {
	unity_window_management_window_mapped (self, plugin, window);
}


static void _unity_window_management_window_destroyed_unity_plugin_window_destroyed (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self) {
	unity_window_management_window_destroyed (self, plugin, window);
}


static void _unity_window_management_kill_window_effects_unity_plugin_kill_window_effects (UnityPlugin* _sender, UnityPlugin* plugin, MutterWindow* window, gpointer self) {
	unity_window_management_kill_window_effects (self, plugin, window);
}


UnityWindowManagement* unity_window_management_construct (GType object_type, UnityPlugin* p) {
	UnityWindowManagement * self;
	UnityPlugin* _tmp0_;
	g_return_val_if_fail (p != NULL, NULL);
	self = (UnityWindowManagement*) g_object_new (object_type, NULL);
	self->priv->plugin = (_tmp0_ = _g_object_ref0 (p), _g_object_unref0 (self->priv->plugin), _tmp0_);
	g_signal_connect_object (self->priv->plugin, "window-minimized", (GCallback) _unity_window_management_window_minimized_unity_plugin_window_minimized, self, 0);
	g_signal_connect_object (self->priv->plugin, "window-maximized", (GCallback) _unity_window_management_window_maximized_unity_plugin_window_maximized, self, 0);
	g_signal_connect_object (self->priv->plugin, "window-unmaximized", (GCallback) _unity_window_management_window_unmaximized_unity_plugin_window_unmaximized, self, 0);
	g_signal_connect_object (self->priv->plugin, "window-mapped", (GCallback) _unity_window_management_window_mapped_unity_plugin_window_mapped, self, 0);
	g_signal_connect_object (self->priv->plugin, "window-destroyed", (GCallback) _unity_window_management_window_destroyed_unity_plugin_window_destroyed, self, 0);
	g_signal_connect_object (self->priv->plugin, "kill-window-effects", (GCallback) _unity_window_management_kill_window_effects_unity_plugin_kill_window_effects, self, 0);
	return self;
}


UnityWindowManagement* unity_window_management_new (UnityPlugin* p) {
	return unity_window_management_construct (UNITY_TYPE_WINDOW_MANAGEMENT, p);
}


static gint unity_window_management_get_animation_speed (UnityWindowManagement* self, MutterWindow* window) {
	gint result = 0;
	gint type;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (window != NULL, 0);
	type = (gint) mutter_window_get_window_type (window);
	if (type == META_COMP_WINDOW_NORMAL) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = type == META_COMP_WINDOW_DIALOG;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = type == META_COMP_WINDOW_MODAL_DIALOG;
	}
	if (_tmp0_) {
		result = 200;
		return result;
	}
	result = 80;
	return result;
}


static void unity_window_management_window_maximized (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (window != NULL);
	g_object_set_data_full ((GObject*) window, unity_maximus_user_unmaximize_hint, NULL, NULL);
	mutter_plugin_maximize_completed (unity_plugin_get_plugin (plugin), window);
}


static void unity_window_management_window_unmaximized (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window, gint x, gint y, gint width, gint height) {
	gint i;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (window != NULL);
	i = 1;
	g_object_set_data_full ((GObject*) window, unity_maximus_user_unmaximize_hint, GINT_TO_POINTER (i), NULL);
	mutter_plugin_unmaximize_completed (unity_plugin_get_plugin (plugin), window);
}


static void _unity_window_management_window_minimized_completed_clutter_animation_completed (ClutterAnimation* _sender, gpointer self) {
	unity_window_management_window_minimized_completed (self, _sender);
}


static void unity_window_management_window_minimized (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window) {
	gint type;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	MetaRectangle _tmp3_ = {0};
	MetaRectangle rect;
	gint speed;
	ClutterAnimation* anim;
	MutterWindow* _tmp4_;
	ClutterActor* actor;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (window != NULL);
	type = (gint) mutter_window_get_window_type (window);
	if (type != META_WINDOW_NORMAL) {
		_tmp2_ = type != META_WINDOW_DIALOG;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		_tmp1_ = type != META_WINDOW_MODAL_DIALOG;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = type != META_WINDOW_MENU;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		mutter_plugin_minimize_completed (unity_plugin_get_plugin (self->priv->plugin), window);
		return;
	}
	rect = (_tmp3_.height = 0, _tmp3_.width = 0, _tmp3_.x = 0, _tmp3_.y = 0, _tmp3_);
	speed = unity_window_management_get_animation_speed (self, window);
	anim = NULL;
	actor = _g_object_ref0 ((_tmp4_ = window, CLUTTER_IS_ACTOR (_tmp4_) ? ((ClutterActor*) _tmp4_) : NULL));
	if (meta_window_get_icon_geometry (mutter_window_get_meta_window (window), &rect)) {
		float scale;
		ClutterAnimation* _tmp5_;
		scale = MIN (MIN ((float) 1, rect.width / clutter_actor_get_width (actor)), MIN ((float) 1, rect.height / clutter_actor_get_height (actor)));
		g_object_set ((GObject*) actor, "scale-gravity", CLUTTER_GRAVITY_CENTER, NULL);
		anim = (_tmp5_ = _g_object_ref0 (clutter_actor_animate (actor, (gulong) CLUTTER_EASE_IN_SINE, (guint) speed, "opacity", 0, "x", (float) ((rect.x + (rect.width / 2)) - (clutter_actor_get_width (actor) / 2)), "y", (float) ((rect.y + (rect.height / 2)) - (clutter_actor_get_height (actor) / 2)), "scale-x", scale, "scale-y", scale, NULL)), _g_object_unref0 (anim), _tmp5_);
	} else {
		ClutterAnimation* _tmp6_;
		anim = (_tmp6_ = _g_object_ref0 (clutter_actor_animate (actor, (gulong) CLUTTER_EASE_IN_SINE, (guint) speed, "opacity", 0, NULL)), _g_object_unref0 (anim), _tmp6_);
	}
	g_signal_connect_object (anim, "completed", (GCallback) _unity_window_management_window_minimized_completed_clutter_animation_completed, self, 0);
	_g_object_unref0 (actor);
	_g_object_unref0 (anim);
}


static void unity_window_management_window_minimized_completed (UnityWindowManagement* self, ClutterAnimation* anim) {
	GObject* _tmp0_;
	MutterWindow* window;
	g_return_if_fail (self != NULL);
	g_return_if_fail (anim != NULL);
	window = (_tmp0_ = clutter_animation_get_object (anim), MUTTER_IS_WINDOW (_tmp0_) ? ((MutterWindow*) _tmp0_) : NULL);
	if (window == NULL) {
		return;
	}
	clutter_actor_hide ((ClutterActor*) window);
	mutter_plugin_minimize_completed (unity_plugin_get_plugin (self->priv->plugin), window);
}


static gboolean unity_window_management_force_activate (UnityWindowManagement* self) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	if (MUTTER_IS_WINDOW (self->priv->last_mapped)) {
		MetaWindow* w;
		MetaDisplay* d;
		w = mutter_window_get_meta_window (self->priv->last_mapped);
		d = meta_window_get_display (w);
		meta_window_activate (mutter_window_get_meta_window (self->priv->last_mapped), meta_display_get_current_time (d));
	}
	result = FALSE;
	return result;
}


static gboolean _unity_window_management_force_activate_gsource_func (gpointer self) {
	gboolean result;
	result = unity_window_management_force_activate (self);
	return result;
}


static void _unity_window_management_window_mapped_completed_clutter_animation_completed (ClutterAnimation* _sender, gpointer self) {
	unity_window_management_window_mapped_completed (self, _sender);
}


static void unity_window_management_window_mapped (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window) {
	gint type;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	ClutterAnimation* anim;
	MutterWindow* _tmp4_;
	ClutterActor* actor;
	gint speed;
	MetaRectangle _tmp5_ = {0};
	MetaRectangle rect;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (window != NULL);
	type = (gint) mutter_window_get_window_type (window);
	if (type != META_WINDOW_NORMAL) {
		_tmp2_ = type != META_WINDOW_DIALOG;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		_tmp1_ = type != META_WINDOW_MODAL_DIALOG;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = type != META_WINDOW_MENU;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		mutter_plugin_map_completed (unity_plugin_get_plugin (self->priv->plugin), window);
		return;
	}
	if (unity_expose_manager_get_expose_showing (unity_plugin_get_expose_manager (plugin))) {
		clutter_actor_set_opacity ((ClutterActor*) window, (guint8) 0);
		mutter_plugin_map_completed (unity_plugin_get_plugin (self->priv->plugin), window);
		return;
	}
	if (type == META_WINDOW_NORMAL) {
		_tmp3_ = TRUE;
	} else {
		_tmp3_ = type == META_WINDOW_DIALOG;
	}
	if (_tmp3_) {
		meta_window_activate (mutter_window_get_meta_window (window), meta_window_get_user_time (mutter_window_get_meta_window (window)));
		self->priv->last_mapped = window;
		g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 0, _unity_window_management_force_activate_gsource_func, g_object_ref (self), g_object_unref);
	}
	anim = NULL;
	actor = _g_object_ref0 ((_tmp4_ = window, CLUTTER_IS_ACTOR (_tmp4_) ? ((ClutterActor*) _tmp4_) : NULL));
	clutter_actor_set_opacity (actor, (guint8) 0);
	clutter_actor_show ((ClutterActor*) window);
	speed = unity_window_management_get_animation_speed (self, window);
	rect = (_tmp5_.height = 0, _tmp5_.width = 0, _tmp5_.x = 0, _tmp5_.y = 0, _tmp5_);
	if (meta_window_get_icon_geometry (mutter_window_get_meta_window (window), &rect)) {
		MetaRectangle _tmp6_ = {0};
		ClutterAnimation* _tmp7_;
		rect = (_tmp6_.height = 0, _tmp6_.width = 0, _tmp6_.x = 0, _tmp6_.y = 0, _tmp6_);
		meta_window_get_outer_rect (mutter_window_get_meta_window (window), &rect);
		g_object_set ((GObject*) actor, "scale-gravity", CLUTTER_GRAVITY_CENTER, NULL);
		anim = (_tmp7_ = _g_object_ref0 (clutter_actor_animate (actor, (gulong) CLUTTER_EASE_IN_SINE, (guint) speed, "opacity", 255, "x", (float) rect.x, "y", (float) rect.y, "scale-x", 1.f, "scale-y", 1.f, NULL)), _g_object_unref0 (anim), _tmp7_);
	} else {
		ClutterAnimation* _tmp8_;
		anim = (_tmp8_ = _g_object_ref0 (clutter_actor_animate (actor, (gulong) CLUTTER_EASE_IN_SINE, (guint) speed, "opacity", 255, NULL)), _g_object_unref0 (anim), _tmp8_);
	}
	g_signal_connect_object (anim, "completed", (GCallback) _unity_window_management_window_mapped_completed_clutter_animation_completed, self, 0);
	_g_object_unref0 (actor);
	_g_object_unref0 (anim);
}


static void unity_window_management_window_mapped_completed (UnityWindowManagement* self, ClutterAnimation* anim) {
	GObject* _tmp0_;
	MutterWindow* window;
	MutterWindow* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (anim != NULL);
	window = (_tmp0_ = clutter_animation_get_object (anim), MUTTER_IS_WINDOW (_tmp0_) ? ((MutterWindow*) _tmp0_) : NULL);
	if (window == NULL) {
		return;
	}
	clutter_actor_set_opacity ((_tmp1_ = window, CLUTTER_IS_ACTOR (_tmp1_) ? ((ClutterActor*) _tmp1_) : NULL), (guint8) 255);
	mutter_plugin_map_completed (unity_plugin_get_plugin (self->priv->plugin), window);
}


static void _unity_window_management_window_destroyed_completed_clutter_animation_completed (ClutterAnimation* _sender, gpointer self) {
	unity_window_management_window_destroyed_completed (self, _sender);
}


static void unity_window_management_window_destroyed (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window) {
	gint type;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	ClutterAnimation* anim;
	gint speed;
	ClutterAnimation* _tmp3_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (window != NULL);
	type = (gint) mutter_window_get_window_type (window);
	if (type != META_WINDOW_NORMAL) {
		_tmp2_ = type != META_WINDOW_DIALOG;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		_tmp1_ = type != META_WINDOW_MODAL_DIALOG;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		_tmp0_ = type != META_WINDOW_MENU;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		mutter_plugin_destroy_completed (unity_plugin_get_plugin (self->priv->plugin), window);
		return;
	}
	anim = NULL;
	speed = unity_window_management_get_animation_speed (self, window);
	anim = (_tmp3_ = _g_object_ref0 (clutter_actor_animate ((ClutterActor*) window, (gulong) CLUTTER_EASE_IN_SINE, (guint) speed, "opacity", 0, NULL)), _g_object_unref0 (anim), _tmp3_);
	g_signal_connect_object (anim, "completed", (GCallback) _unity_window_management_window_destroyed_completed_clutter_animation_completed, self, 0);
	_g_object_unref0 (anim);
}


static void unity_window_management_window_destroyed_completed (UnityWindowManagement* self, ClutterAnimation* anim) {
	MutterWindow* window;
	g_return_if_fail (self != NULL);
	g_return_if_fail (anim != NULL);
	window = MUTTER_WINDOW (clutter_animation_get_object (anim));
	mutter_plugin_destroy_completed (unity_plugin_get_plugin (self->priv->plugin), window);
}


static void unity_window_management_kill_window_effects (UnityWindowManagement* self, UnityPlugin* plugin, MutterWindow* window) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (window != NULL);
}


static GObject * unity_window_management_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	UnityWindowManagement * self;
	parent_class = G_OBJECT_CLASS (unity_window_management_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = UNITY_WINDOW_MANAGEMENT (obj);
	{
	}
	return obj;
}


static void unity_window_management_class_init (UnityWindowManagementClass * klass) {
	unity_window_management_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (UnityWindowManagementPrivate));
	G_OBJECT_CLASS (klass)->constructor = unity_window_management_constructor;
	G_OBJECT_CLASS (klass)->finalize = unity_window_management_finalize;
}


static void unity_window_management_instance_init (UnityWindowManagement * self) {
	self->priv = UNITY_WINDOW_MANAGEMENT_GET_PRIVATE (self);
}


static void unity_window_management_finalize (GObject* obj) {
	UnityWindowManagement * self;
	self = UNITY_WINDOW_MANAGEMENT (obj);
	_g_object_unref0 (self->priv->plugin);
	G_OBJECT_CLASS (unity_window_management_parent_class)->finalize (obj);
}


GType unity_window_management_get_type (void) {
	static volatile gsize unity_window_management_type_id__volatile = 0;
	if (g_once_init_enter (&unity_window_management_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (UnityWindowManagementClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) unity_window_management_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (UnityWindowManagement), 0, (GInstanceInitFunc) unity_window_management_instance_init, NULL };
		GType unity_window_management_type_id;
		unity_window_management_type_id = g_type_register_static (G_TYPE_OBJECT, "UnityWindowManagement", &g_define_type_info, 0);
		g_once_init_leave (&unity_window_management_type_id__volatile, unity_window_management_type_id);
	}
	return unity_window_management_type_id__volatile;
}




