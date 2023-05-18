#include "Level1.h"

#include <box2d/box2d.h>
#include <maths/quaternion.h>

void Level1::onLoad() {
	// load the assets in from the .scn
	/*const char* scene_asset_filename = "world.scn";
	scene_assets_ = LoadSceneAssets(platform_, scene_asset_filename);

	if (scene_assets_) {
		gef::DebugOut("loaded\n", scene_asset_filename);
		mesh_instance_.set_mesh(GetMeshFromSceneAssets(scene_assets_));
	} else {
		gef::DebugOut("Scene file %s failed to load\n", scene_asset_filename);
	}*/
	
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.5f, 0.5f);

	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	//Player
	Player* player = new Player(*primitive_builder_, *world_, new gef::Vector4(0, 2, -2, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
	player->init(player_fixture_def, b2_dynamicBody);

	entities.push_back(player);

	//Earth
	Entity* earth = new Entity(*primitive_builder_, *world_, new gef::Vector4(0, 2, -2, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
	earth->init(player_fixture_def, b2_staticBody);
	//earth->set_mesh(mesh_instance_.mesh());

	entities.push_back(earth);

	//Other entity(for collision testing)
	for (int i = 0; i < 4; i++) {
		Entity* entity = new Entity(*primitive_builder_, *world_, new gef::Vector4(-2 + i, 1, -2, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
		entity->init(player_fixture_def, b2_dynamicBody);

		entities.push_back(entity);
	}

	//Ground
	Entity* ground = new Entity(*primitive_builder_, *world_, new gef::Vector4(0, -2, -2, 1), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(10, 1, 1, 1));

	b2PolygonShape shape;
	shape.SetAsBox(ground->getScale()->x() * 0.5f, ground->getScale()->y() * 0.5f);

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;

	ground->init(fixture_def, b2_staticBody);

	entities.push_back(ground);
}

void Level1::update() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->update();
		(*it)->processInput(NULL, input_manager_->keyboard());
	}
}

void Level1::render() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		Entity* entity = (*it);
		const gef::MeshInstance* mesh = static_cast<gef::MeshInstance*>(entity);
		renderer_3d_->DrawMesh(*mesh);
	}
}
