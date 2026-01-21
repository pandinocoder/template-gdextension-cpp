#include "stl.h"

#include <godot_cpp/variant/packed_byte_array.hpp>

namespace godot {
    ::std::string to_stl_utf8(const ::godot::String &value) {
        const auto buffer = value.to_utf8_buffer();
        return ::std::string((const char *)buffer.ptr(), (size_t)buffer.size());
    }

    ::std::string to_stl_utf8(const ::godot::StringName &value) {
        const auto buffer = value.to_utf8_buffer();
        return ::std::string((const char *)buffer.ptr(), (size_t)buffer.size());
    }
}