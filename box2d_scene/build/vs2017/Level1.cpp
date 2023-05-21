#include "Level1.h"

#include <box2d/box2d.h>
#include <maths/quaternion.h>

#include <system/debug_log.h>

#include <LevelMaker.h>

void Level1::onLoad() {
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.5f, 0.5f);

	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	//Player
	Player* player = new Player("Player", * primitive_builder_, *world_, new gef::Vector4((-(LevelSizeX / 2) + 1), 2, -2, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
	
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(player->getPosition()->x(), player->getPosition()->y());
	body_def.fixedRotation = true;

	player->init(body_def);

	entities.push_back(player);

	//Earth
	//Entity* earth = new Entity(*primitive_builder_, *world_, new gef::Vector4(0, 2, -2, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
	//earth->init(player_fixture_def, b2_staticBody);
	//earth->set_mesh(mesh_instance_.mesh());

	//entities.push_back(earth);
	
	int map[LevelSizeX][LevelSizeY] = {
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 1, 1, 1, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 1, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 1, 0, 1, 1, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	{ 1, 0, 0, 0, 0, 0},
	};

	auto e = LevelMaker::createLevel(-16, -8, map, primitive_builder_, world_);
	
	for (auto it = e.begin(); it != e.end(); it++) {
		entities.push_back((*it));
	}
}

void Level1::update() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->update();
		(*it)->processInput(input_manager_);
	}
}

void Level1::render() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		Entity* entity = (*it);
		const gef::MeshInstance* mesh = static_cast<gef::MeshInstance*>(entity);
		renderer_3d_->DrawMesh(*mesh);
	}
}
