#ifndef BALL_MOVEMENT_H
#define BALL_MOVEMENT_H

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

    class Ball : public CharacterBody2D {
        GDCLASS(Ball, CharacterBody2D)

    private:
        Vector2 velocity;
        float speed = 300.0f;

    public:
        static void _bind_methods();
        void _ready();
        void _physics_process(double delta);

        void set_velocity(Vector2 p_velocity);
        Vector2 get_velocity() const;
    };

}

#endif