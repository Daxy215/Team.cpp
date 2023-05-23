#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <math.h>
#include <graphics/renderer_3d.h>

#include "Gun.h"

#include <Entity.h>

#define poolSize 8

namespace gef {
	class Renderer3D;
}

class Player : public Entity {
public:
	Player(std::string name_, PrimitiveBuilder& builder_, b2World& world_, gef::Vector4* position_, gef::Quaternion* rotation_, 
		gef::Vector4* scale_)
		: Entity(name_, builder_, world_, position_, rotation_, scale_) {
		initA();
	}
	
	void initA();
	virtual void update();
	virtual void render(gef::Renderer3D* renderer_3d_);
	virtual void processInput(gef::InputManager* input_manager_);
	virtual void createMesh();
public:
	void damage(int amount);
	void heal(int amount);

	void addScore(int amount) { score += amount; }
private:
	float speed = 5;

	int health = 10, maxhealth = 15;
	int score = 0;

	int shootIndex = 0;

	float gunAngle = 0;
	float shootingTimer = 0;

	Gun* gun;
	Entity* bulletPool[poolSize];
};
#endif

