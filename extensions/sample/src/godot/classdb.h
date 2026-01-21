#pragma once

#include "godot_cpp/variant/string_name.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <initializer_list>

namespace godot {
    #define BIND_PROPERTY(m_property, m_getter_name, p_getter, m_setter_name, p_setter, m_setter_arg) \
        ::godot::ClassDB::bind_method(::godot::D_METHOD(m_getter_name), p_getter); \
        ::godot::ClassDB::bind_method(::godot::D_METHOD(m_setter_name, m_setter_arg), p_setter); \
        ADD_PROPERTY(m_property, m_setter_name, m_getter_name)

    #define BIND_PROPERTY_READONLY(m_property_type, m_property_name, m_getter_name, p_getter) \
        ::godot::ClassDB::bind_method(::godot::D_METHOD(m_getter_name), p_getter); \
        ADD_PROPERTY( \
            ::godot::PropertyInfo( \
                m_property_type, \
                m_property_name, \
                godot::PROPERTY_HINT_NONE, \
                "", \
                godot::PROPERTY_USAGE_READ_ONLY \
            ), \
            "", \
            m_getter_name \
        )

    #define BIND_STATIC_METHOD(m_class, p_getter, ...) \
        ::godot::ClassDB::bind_static_method( \
            #m_class, \
            ::godot::D_METHOD(__VA_ARGS__), \
            p_getter \
        )

    template<class T>
    inline ::godot::MethodDefinition add_args_to_method(
        ::godot::MethodDefinition p_method_definition,
        std::initializer_list<T> p_arg_names
    ) {
        for (const auto &p_arg_name : p_arg_names) {
            p_method_definition.args.push_back(p_arg_name);
        }
        return p_method_definition;
    }

    template<typename... Args>
    inline ::godot::MethodDefinition define_method_with_args(
        ::godot::StringName p_method_name,
        Args... args
    ) {
        ::godot::MethodDefinition method(p_method_name);
        return add_args_to_method(method, args...);
    }

    inline ::godot::MethodDefinition define_method_with_args(
        ::godot::StringName p_method_name,
        std::initializer_list<::godot::StringName> p_arg_names
    ) {
        ::godot::MethodDefinition method(p_method_name);
        for (const auto &p_arg_name : p_arg_names) {
            method.args.push_back(p_arg_name);
        }
        return method;
    }

    // #define BIND_STATIC_PROPERTY(m_property_type, m_class_name, m_property_name, m_getter_name, p_getter, m_setter_name, p_setter, m_setter_arg) \
    //     ::godot::ClassDB::bind_static_method(m_class_name, ::godot::D_METHOD(m_getter_name), p_getter); \
    //     ::godot::ClassDB::bind_static_method(m_class_name, ::godot::D_METHOD(m_setter_name, m_setter_arg), p_setter); \
    //     ADD_PROPERTY( \
    //         ::godot::PropertyInfo( \
    //             m_property_type, \
    //             m_property_name, \
    //             godot::PROPERTY_HINT_NONE, \
    //             "", \
    //             godot::PROPERTY_USAGE_READ_ONLY \
    //         ), \
    //         m_setter_name, \
    //         m_getter_name \
    //     )

    // #define BIND_STATIC_PROPERTY_READONLY(m_property_type, m_class_name, m_property_name, m_getter_name, p_getter) \
    //     ::godot::ClassDB::bind_static_method(m_class_name, ::godot::D_METHOD(m_getter_name), p_getter); \
    //     ADD_PROPERTY( \
    //         ::godot::PropertyInfo( \
    //             m_property_type, \
    //             m_property_name, \
    //             godot::PROPERTY_HINT_NONE, \
    //             "", \
    //             godot::PROPERTY_USAGE_READ_ONLY \
    //         ), \
    //         "", \
    //         m_getter_name \
    //     )

    #define BIND_PROPERTY_READONLY_INFO(m_property_info, m_getter_name, p_getter) \
        ::godot::ClassDB::bind_method(::godot::D_METHOD(m_getter_name), p_getter); \
        ADD_PROPERTY( \
            m_property_info, \
            "", \
            m_getter_name \
        )

    #define INLINE_STRING_NAME(m_name, m_value) \
        inline const ::godot::StringName &m_name() { \
            static auto string_name = ::godot::StringName(m_value, true); \
            return string_name; \
        }
}
