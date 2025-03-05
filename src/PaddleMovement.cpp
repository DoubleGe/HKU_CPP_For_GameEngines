#include "PaddleMovement.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

void PaddleMovement::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &PaddleMovement::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &PaddleMovement::get_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void PaddleMovement::_ready() {
	add_to_group("paddle");
}

void PaddleMovement::_process(double delta) 
{
	Engine* engine{ Engine::get_singleton() };
	if (engine->is_editor_hint()) return;

	Vector2 velocity = Vector2();

	if (Input::get_singleton()->is_action_pressed("move_left")) {
		velocity.x -= speed;
	}
	if (Input::get_singleton()->is_action_pressed("move_right")) {
		velocity.x += speed;
	}

	velocity = velocity.normalized() * speed;
	set_velocity(velocity);
	move_and_slide();
}

void PaddleMovement::set_speed(float p_speed) {
	speed = p_speed;
}

float PaddleMovement::get_speed() const {
	return speed;
}
