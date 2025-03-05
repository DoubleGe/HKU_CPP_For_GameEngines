#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>  
#include <godot_cpp/classes/sprite2d.hpp>

#include "BrickSpawner.h"

using namespace godot;

void BrickSpawner::_bind_methods() {
    ClassDB::bind_method(D_METHOD("SpawnBricks"), &BrickSpawner::SpawnBricks);

    ClassDB::bind_method(D_METHOD("SetBrickPrefab"), &BrickSpawner::SetBrickPrefab);
    ClassDB::bind_method(D_METHOD("GetBrickPrefab"), &BrickSpawner::GetBrickPrefab);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "brickPrefab", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"),
        "SetBrickPrefab", "GetBrickPrefab");

    ClassDB::bind_method(D_METHOD("SetBrickSprites"), &BrickSpawner::SetBrickSprites);
    ClassDB::bind_method(D_METHOD("GetBrickSprites"), &BrickSpawner::GetBrickSprites);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "brickSprites", PROPERTY_HINT_ARRAY_TYPE,
        String::num_int64(Variant::OBJECT) + ":" + Texture2D::get_class_static()),
        "SetBrickSprites", "GetBrickSprites");
}

void BrickSpawner::_ready() {
    SpawnBricks();
}

void BrickSpawner::SpawnBricks() {
    if (!brickPrefab.is_valid()) {
        UtilityFunctions::printerr("BrickSpawner: No valid brick prefab set!");
        return;
    }

    float spacingX = brick_width;
    float spacingY = brick_height;

    float totalWidth = columns * spacingX;
    Vector2 startPosition(totalWidth / -2 + spacingX * .5f, -280);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Node* brickInstance = brickPrefab->instantiate();
            Node2D* brick = Object::cast_to<Node2D>(brickInstance);

            if (brick) {
                Vector2 position = startPosition + Vector2(col * spacingX, row * spacingY);
                brick->set_position(position);

                if (brickSprites.size() > 0) {
                    Sprite2D* sprite = brick->get_node<Sprite2D>("Sprite2D");
                    if (sprite) {
                        int randomIndex = rand() % brickSprites.size();
                        Ref<Texture2D> texture = brickSprites[randomIndex];
                        if (texture.is_valid()) {
                            sprite->set_texture(texture);
                        }
                    }
                }

                add_child(brick);
                brick->set_owner(get_tree()->get_edited_scene_root());
            }
            else {
                UtilityFunctions::printerr("BrickSpawner: Failed to cast brick to Node2D!");
                memdelete(brickInstance);
            }
        }
    }
}

void BrickSpawner::SetBrickPrefab(const Ref<PackedScene>& pBrickPrefab) {
    brickPrefab = pBrickPrefab;
}

Ref<PackedScene> BrickSpawner::GetBrickPrefab() const {
    return brickPrefab;
}

void BrickSpawner::SetBrickSprites(const Array& pBrickSprites) {
    brickSprites = pBrickSprites;
}

Array BrickSpawner::GetBrickSprites() const {
    return brickSprites;
}