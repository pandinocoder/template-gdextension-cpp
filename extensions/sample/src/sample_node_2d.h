#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/math_defs.hpp>

using namespace godot;

namespace sample {

    class SampleNode2D : public Node2D {
        GDCLASS(SampleNode2D, Node2D)

    private:
        godot::real_t _angle;

    protected:
        static void _bind_methods();

    public:
        SampleNode2D();
        ~SampleNode2D();

        void _process(double delta) override;

        ::godot::real_t get_angle() const;
        void set_angle(::godot::real_t p_value);

        ::godot::real_t get_angle_reload() const;
        void set_angle_reload(::godot::real_t p_value);
    };

}