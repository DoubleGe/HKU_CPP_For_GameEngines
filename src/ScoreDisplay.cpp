#include "ScoreDisplay.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "GameState.h"

namespace godot {
	ScoreDisplay::ScoreDisplay() {
		score_label = nullptr;
	}

	ScoreDisplay::~ScoreDisplay() {

	}

	void ScoreDisplay::_bind_methods()
	{
		ClassDB::bind_method(D_METHOD("AddScore", "value"), &ScoreDisplay::AddScore);
		ClassDB::bind_method(D_METHOD("ResetScore"), &ScoreDisplay::ResetScore);
	}

	void ScoreDisplay::_ready() {
		Engine* engine{ Engine::get_singleton() };
		if (engine->is_editor_hint()) return;

		score_label = get_node<Label>("ScoreLabel");
		UpdateScoreText();
	}

	void ScoreDisplay::AddScore(int value) {
		GameState* gameState = Object::cast_to<GameState>(get_node<Node>("/root/GlobalGameState"));
		if (gameState) gameState->AddScore(value);
		
		UpdateScoreText();
	}

	void ScoreDisplay::ResetScore() {
		GameState* gameState = Object::cast_to<GameState>(get_node<Node>("/root/GlobalGameState"));
		if (gameState) gameState->ResetScore();
		UpdateScoreText();
	}

	void ScoreDisplay::UpdateScoreText() {
		if (score_label) {
			GameState* gameState = Object::cast_to<GameState>(get_node<Node>("/root/GlobalGameState"));
			if (gameState) {
				int score = gameState->GetScore();
				String formatted_score = String::num_int64(score).pad_zeros(8);
				score_label->set_text(formatted_score);
			}
		}
	}
}