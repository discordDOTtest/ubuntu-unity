/* quicklist-view.c generated by valac 0.10.0, the Vala compiler
 * generated from quicklist-view.vala, do not modify */

/* -*- Mode: vala; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*- */
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
 * Authored by Gordon Allott <gord.allott@canonical.com>,
 *             Mirco "MacSlow" Müller <mirco.mueller@canonical.com>
 *
 */

#include <glib.h>
#include <glib-object.h>
#include <float.h>
#include <math.h>
#include <clutk/clutk.h>
#include <clutter/clutter.h>


#define UNITY_LAUNCHER_TYPE_QUICKLIST_MENU (unity_launcher_quicklist_menu_get_type ())
#define UNITY_LAUNCHER_QUICKLIST_MENU(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), UNITY_LAUNCHER_TYPE_QUICKLIST_MENU, UnityLauncherQuicklistMenu))
#define UNITY_LAUNCHER_QUICKLIST_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), UNITY_LAUNCHER_TYPE_QUICKLIST_MENU, UnityLauncherQuicklistMenuClass))
#define UNITY_LAUNCHER_IS_QUICKLIST_MENU(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), UNITY_LAUNCHER_TYPE_QUICKLIST_MENU))
#define UNITY_LAUNCHER_IS_QUICKLIST_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), UNITY_LAUNCHER_TYPE_QUICKLIST_MENU))
#define UNITY_LAUNCHER_QUICKLIST_MENU_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), UNITY_LAUNCHER_TYPE_QUICKLIST_MENU, UnityLauncherQuicklistMenuClass))

typedef struct _UnityLauncherQuicklistMenu UnityLauncherQuicklistMenu;
typedef struct _UnityLauncherQuicklistMenuClass UnityLauncherQuicklistMenuClass;
typedef struct _UnityLauncherQuicklistMenuPrivate UnityLauncherQuicklistMenuPrivate;

struct _UnityLauncherQuicklistMenu {
	CtkMenuExpandable parent_instance;
	UnityLauncherQuicklistMenuPrivate * priv;
};

struct _UnityLauncherQuicklistMenuClass {
	CtkMenuExpandableClass parent_class;
};

struct _UnityLauncherQuicklistMenuPrivate {
	gint last_width;
	gint last_height;
	float cached_x;
	float cached_y;
};


static gpointer unity_launcher_quicklist_menu_parent_class = NULL;

#define UNITY_LAUNCHER_LINE_WIDTH 0.083f
#define UNITY_LAUNCHER_LINE_WIDTH_ABS 1.5f
#define UNITY_LAUNCHER_TEXT_HEIGHT 1.0f
#define UNITY_LAUNCHER_MAX_TEXT_WIDTH 15.0f
#define UNITY_LAUNCHER_GAP 0.25f
#define UNITY_LAUNCHER_MARGIN 0.5f
#define UNITY_LAUNCHER_BORDER 0.25f
#define UNITY_LAUNCHER_CORNER_RADIUS 0.3f
#define UNITY_LAUNCHER_CORNER_RADIUS_ABS 5.0f
#define UNITY_LAUNCHER_SHADOW_SIZE 1.25f
#define UNITY_LAUNCHER_ITEM_HEIGHT 2.0f
#define UNITY_LAUNCHER_ITEM_CORNER_RADIUS 0.3f
#define UNITY_LAUNCHER_ITEM_CORNER_RADIUS_ABS 4.0f
#define UNITY_LAUNCHER_ITEM_INDENT_ABS 20.0f
#define UNITY_LAUNCHER_ANCHOR_HEIGHT 1.5f
#define UNITY_LAUNCHER_ANCHOR_HEIGHT_ABS 18.0f
#define UNITY_LAUNCHER_ANCHOR_WIDTH 0.75f
#define UNITY_LAUNCHER_ANCHOR_WIDTH_ABS 10.0f
GType unity_launcher_quicklist_menu_get_type (void) G_GNUC_CONST;
#define UNITY_LAUNCHER_QUICKLIST_MENU_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), UNITY_LAUNCHER_TYPE_QUICKLIST_MENU, UnityLauncherQuicklistMenuPrivate))
enum  {
	UNITY_LAUNCHER_QUICKLIST_MENU_DUMMY_PROPERTY
};
static void unity_launcher_quicklist_menu_real_paint (ClutterActor* base);
static void unity_launcher_quicklist_menu_real_allocate (ClutterActor* base, const ClutterActorBox* box, ClutterAllocationFlags flags);
UnityLauncherQuicklistMenu* unity_launcher_quicklist_menu_new (void);
UnityLauncherQuicklistMenu* unity_launcher_quicklist_menu_construct (GType object_type);
static GObject * unity_launcher_quicklist_menu_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void unity_launcher_quicklist_menu_finalize (GObject* obj);



static void unity_launcher_quicklist_menu_real_paint (ClutterActor* base) {
	UnityLauncherQuicklistMenu * self;
	self = (UnityLauncherQuicklistMenu*) base;
	CLUTTER_ACTOR_CLASS (unity_launcher_quicklist_menu_parent_class)->paint ((ClutterActor*) CTK_MENU_EXPANDABLE (self));
}


static void unity_launcher_quicklist_menu_real_allocate (ClutterActor* base, const ClutterActorBox* box, ClutterAllocationFlags flags) {
	UnityLauncherQuicklistMenu * self;
	gint new_width;
	gint new_height;
	gboolean _tmp0_ = FALSE;
	self = (UnityLauncherQuicklistMenu*) base;
	new_width = 0;
	new_height = 0;
	new_width = (gint) ((*box).x2 - (*box).x1);
	new_height = (gint) ((*box).y2 - (*box).y1);
	if (self->priv->last_width == new_width) {
		_tmp0_ = self->priv->last_height == new_height;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		return;
	}
	self->priv->last_width = new_width;
	self->priv->last_height = new_height;
	CLUTTER_ACTOR_CLASS (unity_launcher_quicklist_menu_parent_class)->allocate ((ClutterActor*) CTK_MENU_EXPANDABLE (self), box, flags);
}


UnityLauncherQuicklistMenu* unity_launcher_quicklist_menu_construct (GType object_type) {
	UnityLauncherQuicklistMenu * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


UnityLauncherQuicklistMenu* unity_launcher_quicklist_menu_new (void) {
	return unity_launcher_quicklist_menu_construct (UNITY_LAUNCHER_TYPE_QUICKLIST_MENU);
}


static GObject * unity_launcher_quicklist_menu_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	UnityLauncherQuicklistMenu * self;
	parent_class = G_OBJECT_CLASS (unity_launcher_quicklist_menu_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = UNITY_LAUNCHER_QUICKLIST_MENU (obj);
	{
		ctk_menu_set_spacing ((CtkMenu*) self, 2);
		ctk_menu_expandable_set_content_padding ((CtkMenuExpandable*) self, 0);
		ctk_menu_expandable_set_content_padding_left_right ((CtkMenuExpandable*) self, 4);
		ctk_menu_expandable_set_padding ((CtkMenuExpandable*) self, 16);
		self->priv->last_width = -1;
		self->priv->last_height = -1;
		self->priv->cached_x = 0.0f;
		self->priv->cached_y = 0.0f;
	}
	return obj;
}


static void unity_launcher_quicklist_menu_class_init (UnityLauncherQuicklistMenuClass * klass) {
	unity_launcher_quicklist_menu_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (UnityLauncherQuicklistMenuPrivate));
	CLUTTER_ACTOR_CLASS (klass)->paint = unity_launcher_quicklist_menu_real_paint;
	CLUTTER_ACTOR_CLASS (klass)->allocate = unity_launcher_quicklist_menu_real_allocate;
	G_OBJECT_CLASS (klass)->constructor = unity_launcher_quicklist_menu_constructor;
	G_OBJECT_CLASS (klass)->finalize = unity_launcher_quicklist_menu_finalize;
}


static void unity_launcher_quicklist_menu_instance_init (UnityLauncherQuicklistMenu * self) {
	self->priv = UNITY_LAUNCHER_QUICKLIST_MENU_GET_PRIVATE (self);
}


static void unity_launcher_quicklist_menu_finalize (GObject* obj) {
	UnityLauncherQuicklistMenu * self;
	self = UNITY_LAUNCHER_QUICKLIST_MENU (obj);
	G_OBJECT_CLASS (unity_launcher_quicklist_menu_parent_class)->finalize (obj);
}


GType unity_launcher_quicklist_menu_get_type (void) {
	static volatile gsize unity_launcher_quicklist_menu_type_id__volatile = 0;
	if (g_once_init_enter (&unity_launcher_quicklist_menu_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (UnityLauncherQuicklistMenuClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) unity_launcher_quicklist_menu_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (UnityLauncherQuicklistMenu), 0, (GInstanceInitFunc) unity_launcher_quicklist_menu_instance_init, NULL };
		GType unity_launcher_quicklist_menu_type_id;
		unity_launcher_quicklist_menu_type_id = g_type_register_static (CTK_TYPE_MENU_EXPANDABLE, "UnityLauncherQuicklistMenu", &g_define_type_info, 0);
		g_once_init_leave (&unity_launcher_quicklist_menu_type_id__volatile, unity_launcher_quicklist_menu_type_id);
	}
	return unity_launcher_quicklist_menu_type_id__volatile;
}




