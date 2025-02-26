#ifndef PROPERTY_MACROS_H
#define PROPERTY_MACROS_H

#include <godot_cpp/core/class_db.hpp>

// Macro to automate getter, setter, and property binding
#define DEFINE_PROPERTY(CLASS, TYPE, NAME, DEFAULT, GODOT_TYPE) \
private:                                                        \
    TYPE NAME = DEFAULT;                                        \
                                                                \
public:                                                         \
    void set_##NAME(TYPE p_value) { NAME = p_value; }           \
    TYPE get_##NAME() const { return NAME; }                    \
    static void bind_property_##NAME()                          \
    {                                                           \
        ClassDB::bind_method(D_METHOD("set_" #NAME, #NAME),     \
                             &CLASS::set_##NAME);               \
        ClassDB::bind_method(D_METHOD("get_" #NAME),            \
                             &CLASS::get_##NAME);               \
        ADD_PROPERTY(PropertyInfo(GODOT_TYPE, #NAME),           \
                     "set_" #NAME, "get_" #NAME);               \
    }

#define DEFINE_PROPERTY_OVERRIDE(CLASS, TYPE, NAME, DEFAULT, GODOT_TYPE) \
private:                                                                 \
    TYPE NAME = DEFAULT;                                                 \
                                                                         \
public:                                                                  \
    void set_##NAME(TYPE p_value) { NAME = p_value; }                    \
    TYPE get_##NAME() const override { return NAME; }                    \
    static void bind_property_##NAME()                                   \
    {                                                                    \
        ClassDB::bind_method(D_METHOD("set_" #NAME, #NAME),              \
                             &CLASS::set_##NAME);                        \
        ClassDB::bind_method(D_METHOD("get_" #NAME),                     \
                             &CLASS::get_##NAME);                        \
        ADD_PROPERTY(PropertyInfo(GODOT_TYPE, #NAME),                    \
                     "set_" #NAME, "get_" #NAME);                        \
    }

#endif // PROPERTY_MACROS_H