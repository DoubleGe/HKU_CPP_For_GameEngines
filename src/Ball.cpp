#include "Ball.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Ball::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_velocity", "velocity"), &Ball::set_velocity);
    ClassDB::bind_method(D_METHOD("get_velocity"), &Ball::get_velocity);
}

void Ball::_ready() {
    Ref<RandomNumberGenerator> rng = memnew(RandomNumberGenerator);
    velocity = Vector2(rng->randf_range(-1.0, 1.0), -1.0).normalized() * speed;
}

void Ball::_physics_process(double delta) {
    Engine* engine{ Engine::get_singleton() };
    if (engine->is_editor_hint()) return;

    Vector2 motion = velocity * delta;
    Ref<KinematicCollision2D> collision = move_and_collide(motion);


    if (collision.is_valid()) {
        Vector2 normal = collision->get_normal(); 
        velocity = velocity.bounce(normal);       
    }
}

void Ball::set_velocity(Vector2 p_velocity) {
    velocity = p_velocity.normalized() * speed;
}

Vector2 Ball::get_velocity() const {
    return velocity;
}
