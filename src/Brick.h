#ifndef BRICK_H
#define BRICK_H

#include <godot_cpp/classes/static_body2d.hpp>   

namespace godot {

    class Brick : public StaticBody2D {
        GDCLASS(Brick, StaticBody2D)

    public:
        static void _bind_methods();

        void _ready();
        void destroy();
    };

}

#endif