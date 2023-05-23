#ifndef LEVEL1_H
#define LEVEL1_H

#include <SceneA.h>

#include <string>
//#include <graphics/mesh_instance.h>

#include <Player.h>

namespace gef {
	class Renderer3D;
}

class Level1 : public SceneA {
public:
	Level1(std::string name, gef::Renderer3D* renderer_3d_, PrimitiveBuilder* primitive_builder_, b2World* world_, gef::InputManager* input_manager_) : SceneA(name),
		renderer_3d_(renderer_3d_), primitive_builder_(primitive_builder_), world_(world_), input_manager_(input_manager_) {}

	virtual void onLoad();
	virtual void onUnLoad() {}
	virtual void update();
	virtual void render();

public:
	Player* player;
public:
	gef::Renderer3D* renderer_3d_;
	PrimitiveBuilder* primitive_builder_;
	b2World* world_;

	gef::InputManager* input_manager_;
};

#endif // !SPLASHSCREEN_H