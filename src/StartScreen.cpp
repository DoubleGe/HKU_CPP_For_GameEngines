#include "StartScreen.h"

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

StartScreen::StartScreen() {
	startButton = nullptr;
	quitButton = nullptr;
}

StartScreen::~StartScreen() {
}

void StartScreen::_bind_methods() {
	ClassDB::bind_method(D_METHOD("OnStartButtonPressed"), &StartScreen::OnStartButtonPressed);
	ClassDB::bind_method(D_METHOD("OnQuitButtonPressed"), &StartScreen::OnQuitButtonPressed);
}

void StartScreen::_ready() {
	Engine* engine{ Engine::get_singleton() };
	if (engine->is_editor_hint()) return;

	startButton = get_node<Button>("StartButton");
	quitButton = get_node<Button>("QuitButton");

	if (startButton) {
		startButton->connect("pressed", callable_mp(this, &StartScreen::OnStartButtonPressed));
	}
	if (quitButton) {
		quitButton->connect("pressed", callable_mp(this, &StartScreen::OnQuitButtonPressed));
	}
}

void StartScreen::OnStartButtonPressed() {
	get_tree()->change_scene_to_file("res://Scenes/Game.tscn");
}

void StartScreen::OnQuitButtonPressed()
{
	get_tree()->quit();
}
