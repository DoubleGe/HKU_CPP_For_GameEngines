#ifndef BRICK_SPAWNER_H
#define BRICK_SPAWNER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include "Brick.h"

namespace godot {

    class BrickSpawner : public Node2D {
        GDCLASS(BrickSpawner, Node2D)

    private:
        Ref<PackedScene> brickPrefab;
        Array brickSprites;

        int rows = 5; 
        int columns = 10; 
        float brick_width = 114; 
        float brick_height = 24;

        int activeBricks;
    public:
        static void _bind_methods();

        void _ready();
        void SpawnBricks();

        void SetBrickPrefab(const Ref<PackedScene>& p_brick_scene);
        Ref<PackedScene> GetBrickPrefab() const;

        void SetBrickSprites(const Array& pBrickSprites);
        Array GetBrickSprites() const;

        void OnBrickDestroyed();
    };

}

#endif
