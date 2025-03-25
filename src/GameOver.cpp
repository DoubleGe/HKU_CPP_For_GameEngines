#include "GameOver.h"
#include "GameState.h"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

void GameOver::_bind_methods() {
	ClassDB::bind_method(D_METHOD("OnRestartButtonPressed"), &GameOver::OnRestartButtonPressed);
	ClassDB::bind_method(D_METHOD("OnQuitButtonPressed"), &GameOver::OnQuitButtonPressed);
}

GameOver::GameOver() {
	currentScoreLabel = nullptr;
	highScoreLabel = nullptr;
	highScore = 0;
}

GameOver::~GameOver() {}

void GameOver::_ready() {
	Engine* engine{ Engine::get_singleton() };
	if (engine->is_editor_hint()) return;

	currentScoreLabel = get_node<Label>("CurrentScoreLabel");
	highScoreLabel = get_node<Label>("HighScoreLabel");

	GameState* gameState = Object::cast_to<GameState>(get_node<Node>("/root/GlobalGameState"));
	int currentScore = 0;
	if (gameState) {
		currentScore = gameState->GetScore();
	}

	if (currentScoreLabel) {
		currentScoreLabel->set_text("Score: " + String::num_int64(currentScore));
	}

	LoadHighScore();

	if (highScoreLabel) {
		highScoreLabel->set_text("Highscore: " + String::num_int64(highScore));
	}

	if (currentScore > highScore) {
		highScore = currentScore;
		SaveHighScore();
		if (highScoreLabel) {
			highScoreLabel->set_text("Highscore: " + String::num_int64(highScore));
		}
	}

	Button* restartButton = get_node<Button>("RestartButton");
	if (restartButton) {
		restartButton->connect("pressed", Callable(this, "OnRestartButtonPressed"));
	}

	Button* quitButton = get_node<Button>("QuitButton");
	if (quitButton) {
		quitButton->connect("pressed", callable_mp(this, &GameOver::OnQuitButtonPressed));
	}
}

void GameOver::LoadHighScore() {
	String path = "user://highscore.dat";

	if (FileAccess::file_exists(path)) {
		Ref<FileAccess> file = FileAccess::open(path, FileAccess::READ);
		if (file.is_valid()) {
			highScore = file->get_32();
			file->close();
		}
		else {
			UtilityFunctions::print("Error: Could not open highscore file for reading");
			highScore = 0;
		}
	}
	else {
		highScore = 0;
	}
}

void GameOver::SaveHighScore() {
	String path = "user://highscore.dat";

	Ref<FileAccess> file = FileAccess::open(path, FileAccess::WRITE);
	if (file.is_valid()) {
		file->store_32(highScore);
		file->close();
	}
	else {
		UtilityFunctions::print("Error: Could not open highscore file for writing");
	}
}

void GameOver::OnRestartButtonPressed() {
	GameState* gameState = Object::cast_to<GameState>(get_node<Node>("/root/GlobalGameState"));
	if (gameState) {
		gameState->ResetScore();
	}

	get_tree()->change_scene_to_file("res://Scenes/Game.tscn");
}

void GameOver::OnQuitButtonPressed()
{
	get_tree()->quit();
}