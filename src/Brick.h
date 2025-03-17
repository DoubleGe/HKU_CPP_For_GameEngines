#ifndef BRICK_H
#define BRICK_H

#include <godot_cpp/classes/static_body2d.hpp>   
#include <godot_cpp/classes/audio_stream_player2d.hpp>

namespace godot {

    class Brick : public StaticBody2D {
        GDCLASS(Brick, StaticBody2D)

    private:
        AudioStreamPlayer2D* breakSound;
    public:
        static void _bind_methods();

        Brick();
        ~Brick();
        void _ready();
        void destroy();
    };

}

#endif