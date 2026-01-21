#include "sample_ref_counted.h"

#include <godot/classdb.h>
#include <godot_cpp/core/property_info.hpp>

namespace sample {
    void SampleRefCounted::_bind_methods() {
        BIND_STATIC_METHOD(SampleRefCounted, &SampleRefCounted::create, "create");

        BIND_PROPERTY(
            ::godot::PropertyInfo(::godot::Variant::INT, "integer"),
            "get_integer",
            &SampleRefCounted::get_integer,
            "set_integer",
            &SampleRefCounted::set_integer,
            "p_value"
        );
    }

    SampleRefCounted *SampleRefCounted::create() {
        return memnew(SampleRefCounted);
    }

    int64_t SampleRefCounted::get_integer() const {
        return _integer;
    }

    void SampleRefCounted::set_integer(int64_t p_value) {
        _integer = p_value;
    }
}