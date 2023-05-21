#include "Player.h"

#include <system/debug_log.h>
#include <graphics/material.h>
#include <input/touch_input_manager.h>
#include <maths/quaternion.h>

#include <Windows.h>

// Object rotation variables
float rotationAngle = 0.0f;
float previousMouseX = 0.0f;

void Player::update() {
	updatePhysics();
}

void Player::processInput(gef::InputManager* input_manager_) {
	//TODO: Remove all this code once you want to create the game mechanic.
	/*if (keyboard->IsKeyDown(keyboard->KC_D)) {
		b2Vec2 force(speed, 0);
		body_->ApplyForceToCenter(force, true);
	}

	if (keyboard->IsKeyDown(keyboard->KC_A)) {
		b2Vec2 force(-speed, 0);

		body_->ApplyForceToCenter(force, true);
	}*/

	auto mousePos = input_manager_->touch_manager()->mouse_position();

	// Calculate the difference in mouse position
	float deltaX = mousePos.x - previousMouseX;

	// Update the rotation angle based on the mouse movement
	rotationAngle += deltaX * 0.01f;

	// Update the previous mouse position
	previousMouseX = mousePos.x;

	float lookAt = positionToAngle(mousePos, gef::Vector2(getPosition()->x(), getPosition()->y()));

	rotation_->z = rotationAngle;

	gef::DebugOut("lookat: %F - %F \n", mousePos.x, mousePos.y);
}

void Player::createMesh() {
	gef::Vector4 size = (*scale_) * 0.5f;
	
	set_mesh(builder_.CreateBoxMesh(size));
	
}

void Player::damage() {

}