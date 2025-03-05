#include "Brick.h"

#include <godot_cpp/core/class_db.hpp> 
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Brick::_bind_methods() {
    ClassDB::bind_method(D_METHOD("destroy"), &Brick::destroy);
}


void Brick::_ready() {
    add_to_group("brick");  
}

void Brick::destroy() {
    queue_free(); 
}
