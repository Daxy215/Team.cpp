#include "LevelMaker.h"

#include <primitive_builder.h>
#include <box2d/box2d.h>

#include <maths/vector4.h>
#include <maths/quaternion.h>

#include "Enemy.h"

std::vector<Entity*> LevelMaker::createLevel(int startX, int startY, int level[LevelSizeX][LevelSizeY], PrimitiveBuilder* primitive_builder, b2World* world_) {
    std::vector<Entity*> entities;

    b2PolygonShape player_shape;
    player_shape.SetAsBox(0.5f, 0.5f);

    b2FixtureDef player_fixture_def;
    player_fixture_def.shape = &player_shape;
    player_fixture_def.density = 1.0f;

    for (int i = 0; i < LevelSizeX; i++) {
        for (int j = 0; j < LevelSizeY; j++) {
            int block = level[i][j];

            if (block == 1) {
                Entity* entity = new Entity("Level Bricks", * primitive_builder, *world_, new gef::Vector4(i + startX, j + startY, 0, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
                entity->init(player_fixture_def, b2_staticBody);

                entities.push_back(entity);
            } else if (block == 2) {
                Enemy* entity = new Enemy("Enemy", *primitive_builder, *world_, new gef::Vector4(i + startX, j + startY, 0, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
                entity->init(player_fixture_def, b2_kinematicBody);

                entities.push_back(entity);
            }
        }
    }

    return entities;
}
