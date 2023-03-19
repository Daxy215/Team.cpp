#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <Entity.h>
#include <input/keyboard.h>
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>
#include <input/touch_input_manager.h>

//#include <Windows.h>
namespace gef {
	class InputManager;
}
class Player : public Entity {
public:
	Player(PrimitiveBuilder& builder_, b2World& world_, gef::Vector4* position_, gef::Quaternion* rotation_, 
		gef::Vector4* scale_)

		: Entity(builder_, world_, position_, rotation_, scale_) {

	}
	
	gef::InputManager* inputmanager_;
	gef::Keyboard* keyboard_;
	gef::SonyController* controller_;
	gef::TouchInputManager* Mouse_;

	virtual void update();
	void damage();// { OutputDebugStringA("Player damaged!"); }
};

#endif

