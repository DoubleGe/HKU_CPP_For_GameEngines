#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "Ball.h"
#include "Brick.h"

using namespace godot;

Ball::Ball()
{
	bounceSound = nullptr;
}

Ball::~Ball()
{
}

void Ball::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_velocity", "velocity"), &Ball::set_velocity);
	ClassDB::bind_method(D_METHOD("get_velocity"), &Ball::get_velocity);
}

void Ball::_ready() {
	Ref<RandomNumberGenerator> rng = memnew(RandomNumberGenerator);
	velocity = Vector2(rng->randf_range(-1.0, 1.0), -1.0).normalized() * speed;

	bounceSound = get_node<AudioStreamPlayer2D>("BoingSound");
}

void Ball::_physics_process(double delta) {
	Engine* engine{ Engine::get_singleton() };
	if (engine->is_editor_hint()) return;

	Vector2 motion = velocity * delta;
	Ref<KinematicCollision2D> collision = move_and_collide(motion);

	Vector2 screen_size = get_viewport_rect().size;
	if (get_global_position().y > screen_size.y) {
		UtilityFunctions::print("Game Over!");
		queue_free();
		get_tree()->change_scene_to_file("res://Scenes/GameOver.tscn");
		return;
	}

	if (collision.is_valid()) {
		Object* collider_obj = collision->get_collider();
		Node2D* collider = Object::cast_to<Node2D>(collider_obj);

		if (collider && collider->is_in_group("paddle")) {
			float ball_x = get_global_position().x;
			float paddle_x = collider->get_global_position().x;
			float paddle_width = collider->get_scale().x * 50.0;

			float edge_threshold = 0.25;
			float effect_strength = 0.5;

			if (abs(ball_x - paddle_x) > paddle_width * edge_threshold) {
				float offset = (ball_x - paddle_x) / (paddle_width / 2.0);

				velocity = Vector2(offset * effect_strength, -1.0).normalized() * speed;
			}
			else {
				Vector2 normal = collision->get_normal();
				velocity = velocity.bounce(normal);
			}

			PlayBounceSound();
		}
		else if (collider && collider->is_in_group("brick")) {
			Brick* brick = Object::cast_to<Brick>(collider);
			if (brick) {
				brick->destroy();
			}
			velocity = velocity.bounce(collision->get_normal());
		}
		else {
			Vector2 normal = collision->get_normal();
			velocity = velocity.bounce(normal);

			PlayBounceSound();
		}
	}
}

void Ball::PlayBounceSound()
{
	if (bounceSound && bounceSound->get_stream().is_valid()) {
		bounceSound->play();
	}
}

void Ball::set_velocity(Vector2 p_velocity) {
	velocity = p_velocity.normalized() * speed;
}

Vector2 Ball::get_velocity() const {
	return velocity;
}
