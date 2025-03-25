#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GameState : public Node {
    GDCLASS(GameState, Node)

private:
    int currentScore;

protected:
    static void _bind_methods();

public:
    GameState();
    ~GameState();

    void SetScore(int score);
    int GetScore() const;
    void AddScore(int points);
    void ResetScore();
};

#endif