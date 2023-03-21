#include "Player.h"

#include <Windows.h>

void Player::update(gef::Keyboard* keyboard, gef::InputManager* input_manager, gef::SonyController* controller, gef::TouchInputManager* mouse) {
	//TODO: Handler input system here

	float x = 0;
	float y = 0;
	

	
	if (keyboard->IsKeyPressed(gef::Keyboard::KC_ESCAPE)) {
		//pasues game
	}
	if (keyboard->IsKeyPressed(gef::Keyboard::KC_SPACE)) {
		//use power up, for when this is implemented
	}

	if (keyboard->IsKeyDown(gef::Keyboard::KC_D)) {

		x = GetXPos();
		
		getPosition()->set_x(x + velocity);
	
	}

	if (keyboard->IsKeyDown(gef::Keyboard::KC_A)) {

		y = getPosition()->y();

		getPosition()->set_y(y + velocity);
	}

	if (controller->get_right_trigger() == true) {
		float xaxis = controller->left_stick_x_axis();
		float yaxis = controller->right_stick_y_axis();
		//gets the position of the sticks and would fire one shotgun shot in said direction
	}

	if (controller->buttons_pressed() & gef_SONY_CTRL_START) {
		//pauses game
	}

	updatePhysics();

	if (controller->left_stick_x_axis() >0.8 && controller->left_stick_x_axis() <= 1){

		//moves player right
	}

	if (controller->left_stick_x_axis() < -0.8 && controller->left_stick_x_axis() >= -1) {
		//moves player left
	}
	
}

float Player::GetXPos() {
	return getPosition()->x();
}

void Player::damage() {

}

