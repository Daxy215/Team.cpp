#include "Player.h"

#include <system/debug_log.h>
#include <graphics/material.h>
#include <input/touch_input_manager.h>
#include <maths/quaternion.h>

#include <Windows.h>

void Player::update() {
	updatePhysics();
}

void Player::processInput(gef::InputManager* input_manager_) {
	if (input_manager_->keyboard()->IsKeyDown(input_manager_->keyboard()->KC_LEFT)) {
		gunAngle += 0.05f;
	} else if (input_manager_->keyboard()->IsKeyDown(input_manager_->keyboard()->KC_RIGHT)) {
		gunAngle -= 0.05f;
	}

	//Shoot
	if (input_manager_->keyboard()->IsKeyDown(input_manager_->keyboard()->KC_SPACE)) {

	}
}

void Player::createMesh() {
	gef::Vector4 size = (*scale_) * 0.5f;
	
	set_mesh(builder_.CreateBoxMesh(size));
	
}

void Player::damage(int damage) {

	health = health - damage;
	if (health >= 0) {
		//dies (dont know if this goes here)
	}
}

void Player::heal(int healing) {
	if (health < maxhealth) {
		for (int i = 0; i < healing; i++)
		{
			health = health++;
			if (health = maxhealth) {
				return;
			}
		}
	}
}
