/* object-registry.c generated by valac, the Vala compiler
 * generated from object-registry.vala, do not modify */

/*
 * Copyright (C) 2010 Canonical Ltd
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
#include <gee.h>
#include <stdlib.h>
#include <string.h>
#include <gobject/gvaluecollector.h>


#define UNITY_TESTING_TYPE_OBJECT_REGISTRY (unity_testing_object_registry_get_type ())
#define UNITY_TESTING_OBJECT_REGISTRY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), UNITY_TESTING_TYPE_OBJECT_REGISTRY, UnityTestingObjectRegistry))
#define UNITY_TESTING_OBJECT_REGISTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), UNITY_TESTING_TYPE_OBJECT_REGISTRY, UnityTestingObjectRegistryClass))
#define UNITY_TESTING_IS_OBJECT_REGISTRY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), UNITY_TESTING_TYPE_OBJECT_REGISTRY))
#define UNITY_TESTING_IS_OBJECT_REGISTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), UNITY_TESTING_TYPE_OBJECT_REGISTRY))
#define UNITY_TESTING_OBJECT_REGISTRY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), UNITY_TESTING_TYPE_OBJECT_REGISTRY, UnityTestingObjectRegistryClass))

typedef struct _UnityTestingObjectRegistry UnityTestingObjectRegistry;
typedef struct _UnityTestingObjectRegistryClass UnityTestingObjectRegistryClass;
typedef struct _UnityTestingObjectRegistryPrivate UnityTestingObjectRegistryPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _unity_testing_object_registry_unref0(var) ((var == NULL) ? NULL : (var = (unity_testing_object_registry_unref (var), NULL)))
typedef struct _UnityTestingParamSpecObjectRegistry UnityTestingParamSpecObjectRegistry;

struct _UnityTestingObjectRegistry {
	GTypeInstance parent_instance;
	volatile int ref_count;
	UnityTestingObjectRegistryPrivate * priv;
};

struct _UnityTestingObjectRegistryClass {
	GTypeClass parent_class;
	void (*finalize) (UnityTestingObjectRegistry *self);
};

struct _UnityTestingObjectRegistryPrivate {
	GeeHashMap* object_map;
};

struct _UnityTestingParamSpecObjectRegistry {
	GParamSpec parent_instance;
};


static UnityTestingObjectRegistry* unity_testing_object_registry__registry;
static UnityTestingObjectRegistry* unity_testing_object_registry__registry = NULL;
static gpointer unity_testing_object_registry_parent_class = NULL;

gpointer unity_testing_object_registry_ref (gpointer instance);
void unity_testing_object_registry_unref (gpointer instance);
GParamSpec* unity_testing_param_spec_object_registry (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void unity_testing_value_set_object_registry (GValue* value, gpointer v_object);
void unity_testing_value_take_object_registry (GValue* value, gpointer v_object);
gpointer unity_testing_value_get_object_registry (const GValue* value);
GType unity_testing_object_registry_get_type (void) G_GNUC_CONST;
#define UNITY_TESTING_OBJECT_REGISTRY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), UNITY_TESTING_TYPE_OBJECT_REGISTRY, UnityTestingObjectRegistryPrivate))
enum  {
	UNITY_TESTING_OBJECT_REGISTRY_DUMMY_PROPERTY
};
UnityTestingObjectRegistry* unity_testing_object_registry_new (void);
UnityTestingObjectRegistry* unity_testing_object_registry_construct (GType object_type);
UnityTestingObjectRegistry* unity_testing_object_registry_get_default (void);
void unity_testing_object_registry_register (UnityTestingObjectRegistry* self, const char* name, GObject* object);
GeeArrayList* unity_testing_object_registry_lookup (UnityTestingObjectRegistry* self, const char* name);
static void unity_testing_object_registry_finalize (UnityTestingObjectRegistry* obj);



UnityTestingObjectRegistry* unity_testing_object_registry_construct (GType object_type) {
	UnityTestingObjectRegistry* self;
	GeeHashMap* _tmp0_;
	self = (UnityTestingObjectRegistry*) g_type_create_instance (object_type);
	self->priv->object_map = (_tmp0_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, GEE_TYPE_ARRAY_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), _g_object_unref0 (self->priv->object_map), _tmp0_);
	return self;
}


UnityTestingObjectRegistry* unity_testing_object_registry_new (void) {
	return unity_testing_object_registry_construct (UNITY_TESTING_TYPE_OBJECT_REGISTRY);
}


static gpointer _unity_testing_object_registry_ref0 (gpointer self) {
	return self ? unity_testing_object_registry_ref (self) : NULL;
}


UnityTestingObjectRegistry* unity_testing_object_registry_get_default (void) {
	UnityTestingObjectRegistry* result = NULL;
	if (unity_testing_object_registry__registry == NULL) {
		UnityTestingObjectRegistry* _tmp0_;
		unity_testing_object_registry__registry = (_tmp0_ = unity_testing_object_registry_new (), _unity_testing_object_registry_unref0 (unity_testing_object_registry__registry), _tmp0_);
	}
	result = _unity_testing_object_registry_ref0 (unity_testing_object_registry__registry);
	return result;
}


void unity_testing_object_registry_register (UnityTestingObjectRegistry* self, const char* name, GObject* object) {
	GeeArrayList* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (object != NULL);
	if (!gee_map_contains ((GeeMap*) self->priv->object_map, name)) {
		GeeArrayList* _tmp0_;
		gee_abstract_map_set ((GeeAbstractMap*) self->priv->object_map, name, _tmp0_ = gee_array_list_new (G_TYPE_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL));
		_g_object_unref0 (_tmp0_);
	}
	gee_abstract_collection_add ((GeeAbstractCollection*) (_tmp1_ = (GeeArrayList*) gee_abstract_map_get ((GeeAbstractMap*) self->priv->object_map, name)), object);
	_g_object_unref0 (_tmp1_);
}


GeeArrayList* unity_testing_object_registry_lookup (UnityTestingObjectRegistry* self, const char* name) {
	GeeArrayList* result = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	result = (GeeArrayList*) gee_abstract_map_get ((GeeAbstractMap*) self->priv->object_map, name);
	return result;
}


static void unity_testing_value_object_registry_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void unity_testing_value_object_registry_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		unity_testing_object_registry_unref (value->data[0].v_pointer);
	}
}


static void unity_testing_value_object_registry_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = unity_testing_object_registry_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer unity_testing_value_object_registry_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* unity_testing_value_object_registry_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		UnityTestingObjectRegistry* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = unity_testing_object_registry_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* unity_testing_value_object_registry_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	UnityTestingObjectRegistry** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = unity_testing_object_registry_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* unity_testing_param_spec_object_registry (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	UnityTestingParamSpecObjectRegistry* spec;
	g_return_val_if_fail (g_type_is_a (object_type, UNITY_TESTING_TYPE_OBJECT_REGISTRY), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer unity_testing_value_get_object_registry (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, UNITY_TESTING_TYPE_OBJECT_REGISTRY), NULL);
	return value->data[0].v_pointer;
}


void unity_testing_value_set_object_registry (GValue* value, gpointer v_object) {
	UnityTestingObjectRegistry* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, UNITY_TESTING_TYPE_OBJECT_REGISTRY));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, UNITY_TESTING_TYPE_OBJECT_REGISTRY));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		unity_testing_object_registry_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		unity_testing_object_registry_unref (old);
	}
}


void unity_testing_value_take_object_registry (GValue* value, gpointer v_object) {
	UnityTestingObjectRegistry* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, UNITY_TESTING_TYPE_OBJECT_REGISTRY));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, UNITY_TESTING_TYPE_OBJECT_REGISTRY));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		unity_testing_object_registry_unref (old);
	}
}


static void unity_testing_object_registry_class_init (UnityTestingObjectRegistryClass * klass) {
	unity_testing_object_registry_parent_class = g_type_class_peek_parent (klass);
	UNITY_TESTING_OBJECT_REGISTRY_CLASS (klass)->finalize = unity_testing_object_registry_finalize;
	g_type_class_add_private (klass, sizeof (UnityTestingObjectRegistryPrivate));
}


static void unity_testing_object_registry_instance_init (UnityTestingObjectRegistry * self) {
	self->priv = UNITY_TESTING_OBJECT_REGISTRY_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void unity_testing_object_registry_finalize (UnityTestingObjectRegistry* obj) {
	UnityTestingObjectRegistry * self;
	self = UNITY_TESTING_OBJECT_REGISTRY (obj);
	_g_object_unref0 (self->priv->object_map);
}


GType unity_testing_object_registry_get_type (void) {
	static volatile gsize unity_testing_object_registry_type_id__volatile = 0;
	if (g_once_init_enter (&unity_testing_object_registry_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { unity_testing_value_object_registry_init, unity_testing_value_object_registry_free_value, unity_testing_value_object_registry_copy_value, unity_testing_value_object_registry_peek_pointer, "p", unity_testing_value_object_registry_collect_value, "p", unity_testing_value_object_registry_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (UnityTestingObjectRegistryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) unity_testing_object_registry_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (UnityTestingObjectRegistry), 0, (GInstanceInitFunc) unity_testing_object_registry_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType unity_testing_object_registry_type_id;
		unity_testing_object_registry_type_id = g_type_register_fundamental (g_type_fundamental_next (), "UnityTestingObjectRegistry", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&unity_testing_object_registry_type_id__volatile, unity_testing_object_registry_type_id);
	}
	return unity_testing_object_registry_type_id__volatile;
}


gpointer unity_testing_object_registry_ref (gpointer instance) {
	UnityTestingObjectRegistry* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void unity_testing_object_registry_unref (gpointer instance) {
	UnityTestingObjectRegistry* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		UNITY_TESTING_OBJECT_REGISTRY_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}




