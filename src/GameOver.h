#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;

class GameOver : public Node2D {
    GDCLASS(GameOver, Node2D)

private:
    Label* currentScoreLabel;
    Label* highScoreLabel;
    int highScore;

    void LoadHighScore();
    void SaveHighScore();

protected:
    static void _bind_methods();

public:
    GameOver();
    ~GameOver();

    void _ready() override;
    void OnRestartButtonPressed();
    void OnQuitButtonPressed();
};

#endif