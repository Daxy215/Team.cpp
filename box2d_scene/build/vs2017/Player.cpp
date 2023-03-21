#include "Player.h"

#include <graphics/material.h>

#include <Windows.h>

void Player::update() {
	updatePhysics();
}

void Player::processInput(gef::SonyController* controller, gef::Keyboard* keyboard) {
	
	//float xaxis = controller->left_stick_x_axis();

	if (keyboard->IsKeyDown(keyboard->KC_D)) {
		b2Vec2 force(speed, 0);
		body_->ApplyForceToCenter(force, true);
	}

	if (keyboard->IsKeyDown(keyboard->KC_A)) {
		b2Vec2 force(-speed, 0);

		body_->ApplyForceToCenter(force, true);
	}

	//if (xaxis == 1) {

	//	b2Vec2 force(speed, 0);
	//	body_->ApplyForceToCenter(force, true);
	//}

	//if (xaxis == -1) {

	//	b2Vec2 force(-speed, 0);
	//	body_->ApplyForceToCenter(force, true);
	//}
}

void Player::createMesh() {
	gef::Vector4 size = (*scale_) * 0.5f;
	
	set_mesh(builder_.CreateBoxMesh(size));
}

void Player::damage() {

}