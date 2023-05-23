#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>
#include <math.h>
#include <graphics/renderer_3d.h>
#include <graphics/skinned_mesh_instance.h>
#include "MotionClipPlayer.h"

#include <Entity.h>

#define poolSize 8

namespace gef {
	class Renderer3D;
}

class Enemy : public Entity {
public:
	Enemy(std::string name_, PrimitiveBuilder& builder_, b2World& world_, gef::Vector4* position_, gef::Quaternion* rotation_,
		gef::Vector4* scale_)
		: Entity(name_, builder_, world_, position_, rotation_, scale_) {

	}

	virtual void update() { updatePhysics(); }
	virtual void render(gef::Renderer3D* renderer_3d_) {}
	virtual void processInput(gef::InputManager* input_manager_) {}

};

#endif // !ENEMY_H