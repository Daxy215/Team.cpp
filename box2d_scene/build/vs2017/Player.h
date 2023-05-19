#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include <Entity.h>

//#include <Windows.h>

class Player : public Entity {
public:
	Player(std::string name_, PrimitiveBuilder& builder_, b2World& world_, gef::Vector4* position_, gef::Quaternion* rotation_, 
		gef::Vector4* scale_)
		: Entity(name_, builder_, world_, position_, rotation_, scale_) {
	}
	
	virtual void update();
	virtual void processInput(gef::SonyController* controller, gef::Keyboard* keyboard);
	virtual void createMesh();
	void damage();// { OutputDebugStringA("Player damaged!"); }
private:
	float speed = 5;

};
#endif

