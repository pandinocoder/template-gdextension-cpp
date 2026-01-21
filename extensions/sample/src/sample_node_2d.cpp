#include "sample_node_2d.h"

#include <godot/classdb.h>
#include <godot_cpp/core/math_defs.hpp>

using namespace godot;
using namespace sample;

void SampleNode2D::_bind_methods() {
    BIND_PROPERTY(
        ::godot::PropertyInfo(::godot::Variant::FLOAT, "angle"),
        "get_angle",
        &SampleNode2D::get_angle,
        "set_angle",
        &SampleNode2D::set_angle,
        "p_value"
    );

    // BIND_PROPERTY(
    //     ::godot::PropertyInfo(::godot::Variant::FLOAT, "angle_reload"),
    //     "get_angle_reload",
    //     &SampleNode2D::get_angle_reload,
    //     "set_angle_reload",
    //     &SampleNode2D::set_angle_reload,
    //     "p_value"
    // );
}

void SampleNode2D::_notification(int64_t p_what) {
    switch (p_what) {
        case NOTIFICATION_PROCESS:
        {
            const auto delta = get_process_delta_time();
            _angle += delta * Math_PI / 2.0;
            set_position(Vector2(
                Math::sin((real_t)_angle) * 128.0,
                Math::cos((real_t)_angle) * 128.0
            ));
            break;
        }
    }
}

SampleNode2D::SampleNode2D() {
    _angle = 0.0;
}

SampleNode2D::~SampleNode2D() {
}

::godot::real_t SampleNode2D::get_angle() const {
    return _angle;
}

void SampleNode2D::set_angle(::godot::real_t p_value) {
    _angle = p_value;
}

::godot::real_t SampleNode2D::get_angle_reload() const {
    return _angle;
}

void SampleNode2D::set_angle_reload(::godot::real_t p_value) {
    _angle = p_value;
}
