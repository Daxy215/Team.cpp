#include "LevelMaker.h"

#include <primitive_builder.h>
#include <box2d/box2d.h>

#include <maths/vector4.h>
#include <maths/quaternion.h>

std::vector<Entity*> LevelMaker::createLevel(int level[32][32], PrimitiveBuilder* primitive_builder, b2World* world_) {
    std::vector<Entity*> entities;

    b2PolygonShape player_shape;
    player_shape.SetAsBox(0.5f, 0.5f);

    b2FixtureDef player_fixture_def;
    player_fixture_def.shape = &player_shape;
    player_fixture_def.density = 1.0f;

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int block = level[i][j];

            if (block == 1) {
                Entity* entity = new Entity(*primitive_builder, *world_, new gef::Vector4(i, j, 0, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
                entity->init(player_fixture_def, b2_staticBody);

                entities.push_back(entity);
            }
        }
    }

    return entities;
}
