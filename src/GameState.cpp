#include "GameState.h"
#include <godot_cpp/core/class_db.hpp>

void GameState::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetScore", "score"), &GameState::SetScore);
	ClassDB::bind_method(D_METHOD("GetScore"), &GameState::GetScore);
	ClassDB::bind_method(D_METHOD("AddScore", "points"), &GameState::AddScore);
	ClassDB::bind_method(D_METHOD("ResetScore"), &GameState::ResetScore);
}

GameState::GameState() {
	currentScore = 0;
}

GameState::~GameState() {}

void GameState::SetScore(int score) {
	currentScore = score;
}

int GameState::GetScore() const {
	return currentScore;
}

void GameState::AddScore(int points) {
	currentScore += points;
}

void GameState::ResetScore() {
	currentScore = 0;
}