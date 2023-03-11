#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <Entity.h>

//#include <Windows.h>

class Player : public Entity {
public:
	Player(PrimitiveBuilder& builder_, b2World& world_,
		gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_)
		: Entity(builder_, world_, position_, rotation_, scale_) {

	}

	virtual void update();
	void damage();// { OutputDebugStringA("Player damaged!"); }
};

#endif

