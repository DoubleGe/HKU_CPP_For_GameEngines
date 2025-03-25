#include "Brick.h"
#include "ScoreDisplay.h"
#include "BrickSpawner.h"	

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

using namespace godot;

void Brick::_bind_methods() {
	ClassDB::bind_method(D_METHOD("destroy"), &Brick::destroy);
}

Brick::Brick()
{
	breakSound = nullptr;
}

Brick::~Brick()
{
}


void Brick::_ready() {
	Engine* engine{ Engine::get_singleton() };
	if (engine->is_editor_hint()) return;

	add_to_group("brick");

	breakSound = get_node<AudioStreamPlayer2D>("BreakSound");
}

void Brick::destroy() {

	ScoreDisplay* scoreDisplay = get_node<ScoreDisplay>("/root/Game/ScoreDisplay");
	if (scoreDisplay) scoreDisplay->AddScore(100);

	Node* parent = get_parent();
	BrickSpawner* spawner = Object::cast_to<BrickSpawner>(parent);
	if (spawner) spawner->OnBrickDestroyed();

	if (breakSound && breakSound->get_stream().is_valid()) {
		breakSound->play();
		remove_child(breakSound);
		get_parent()->add_child(breakSound);
		breakSound->set_owner(get_parent());
		breakSound->connect("finished", Callable(breakSound, "queue_free"), CONNECT_ONE_SHOT);
	}
	queue_free();
}
