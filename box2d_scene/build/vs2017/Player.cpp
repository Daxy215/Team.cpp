#include "Player.h"

#include <Windows.h>

void Player::update() {
	//TODO: Handler input system here

	if (keyboard_->IsKeyPressed(gef::Keyboard::KC_ESCAPE)) {
		//pasues game
	}
	if (keyboard_->IsKeyPressed(gef::Keyboard::KC_SPACE)) {
		//use power up, for when this is implemented
	}


	if (controller_->get_right_trigger() == true) {
		float xaxis = controller_->left_stick_x_axis();
		float yaxis = controller_->right_stick_y_axis();
		//gets the position of the sticks and would fire one shotgun shot in said direction
	}

	if (controller_->buttons_pressed() & gef_SONY_CTRL_START) {
		//pauses game
	}

	updatePhysics();

}

void Player::damage() {

}
