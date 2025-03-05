#ifndef PADDLE_MOVEMENT_H
#define PADDLE_MOVEMENT_H

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

    class PaddleMovement : public CharacterBody2D {
        GDCLASS(PaddleMovement, CharacterBody2D)

    private:
        float speed = 400.0f;

    protected:
        static void _bind_methods();

    public:
        void _ready();
        void _process(double delta) override;
        void set_speed(float p_speed);
        float get_speed() const;
    };

}

#endif
