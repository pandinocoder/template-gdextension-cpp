#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace sample {
    class SampleRefCounted : public ::godot::RefCounted {
        GDCLASS(SampleRefCounted, ::godot::RefCounted)

    protected:
        static void _bind_methods();

    public:
        static SampleRefCounted *create();

        int64_t get_integer() const;
        void set_integer(int64_t p_value);

    private:
        int64_t _integer = 0;
    };
}