#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <math.h>
#include <maths/math_utils.h>

#include <Entity.h>

//#include <Windows.h>

#define PI 3.1415926

class Player : public Entity {
public:
	Player(std::string name_, PrimitiveBuilder& builder_, b2World& world_, gef::Vector4* position_, gef::Quaternion* rotation_, 
		gef::Vector4* scale_)
		: Entity(name_, builder_, world_, position_, rotation_, scale_) {
		
	}
	
	virtual void update();
	virtual void processInput(gef::InputManager* input_manager_);
	virtual void createMesh();
public:
	void damage(int amount);// { OutputDebugStringA("Player damaged!"); }
	void heal(int amount);

	//Stolen from my game engine
	float positionToAngle(gef::Vector2 lookAtPos, gef::Vector2 pos) {
		float angle = (float)atan2(lookAtPos.y - pos.y, lookAtPos.x - pos.x);
		//angle = gef::RadToDeg(angle);

		return angle;
	}
private:
	float speed = 5;
	int health = 10;
	int maxhealth = 15;
};
#endif

