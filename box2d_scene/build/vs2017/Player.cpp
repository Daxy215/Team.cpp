#include "Player.h"

#include <graphics/material.h>

#include <Windows.h>

void Player::update() {
	updatePhysics();
}

void Player::processInput(gef::SonyController* controller, gef::Keyboard* keyboard) {
	
}

void Player::createMesh() {
	gef::Vector4 size = (*scale_) * 0.5f;
	
	set_mesh(builder_.CreateBoxMesh(size));
}

void Player::damage() {

}