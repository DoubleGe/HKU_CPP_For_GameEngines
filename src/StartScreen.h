#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

namespace godot {
    class StartScreen : public Node2D {
        GDCLASS(StartScreen, Node2D)

    private:
        Button* startButton;
        Button* quitButton;

    protected:
        static void _bind_methods();

    public:
        StartScreen();
        ~StartScreen();
        void _ready() override;
        void OnStartButtonPressed();
        void OnQuitButtonPressed();
    };
}

#endif