#pragma once

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <string>

namespace godot {
    static ::std::string to_stl_utf8(const ::godot::String &value);
    static ::std::string to_stl_utf8(const ::godot::StringName &value);
}

