#include "ScoreDisplay.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {
	ScoreDisplay::ScoreDisplay() {
		score = 0;
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
		score += value;
		UpdateScoreText();
	}

	void ScoreDisplay::ResetScore() {
		score = 0;
		UpdateScoreText();
	}

	void ScoreDisplay::UpdateScoreText() {
		if (score_label) {
			String formatted_score = String::num_int64(score).pad_zeros(8);
			score_label->set_text(formatted_score);
		}
	}
}