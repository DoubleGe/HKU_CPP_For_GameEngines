#ifndef SCORE_DISPLAY_H
#define SCORE_DISPLAY_H

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>

namespace godot {

    class ScoreDisplay : public Node {
        GDCLASS(ScoreDisplay, Node)

    private:
        int score = 0;         
        Label* score_label;     

    public:
        static void _bind_methods();

        ScoreDisplay();
        ~ScoreDisplay();
        void _ready();
        void AddScore(int value);
        void ResetScore();
        void UpdateScoreText();
    };

}

#endif