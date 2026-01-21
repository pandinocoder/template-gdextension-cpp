#pragma once

#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {
    template <typename... Args>
    void fprint(const char *format, const Args &...p_args) {
        ::godot::UtilityFunctions::print(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fprint(const ::godot::StringName &format, const Args &...p_args) {
        ::godot::UtilityFunctions::print(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fprint_verbose(const char *format, const Args &...p_args) {
        ::godot::UtilityFunctions::print_verbose(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fprint_verbose(const ::godot::StringName &format, const Args &...p_args) {
        ::godot::UtilityFunctions::print_verbose(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fpush_error(const char *format, const Args &...p_args) {
        ::godot::UtilityFunctions::push_error(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fpush_error(const ::godot::StringName &format, const Args &...p_args) {
        ::godot::UtilityFunctions::push_error(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fpush_warning(const char *format, const Args &...p_args) {
        ::godot::UtilityFunctions::push_warning(::godot::vformat(format, p_args...));
    }

    template <typename... Args>
    void fpush_warning(const ::godot::StringName &format, const Args &...p_args) {
        ::godot::UtilityFunctions::push_warning(::godot::vformat(format, p_args...));
    }
}