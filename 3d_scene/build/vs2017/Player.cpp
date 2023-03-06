#include "Player.h"

Player::Player() {

}

void Player::init(PrimitiveBuilder* builder_) {
	const gef::Mesh* mesh = builder_->GetDefaultCubeMesh();

	set_mesh(mesh);

	pos_ = new gef::Vector4(1, 0, 0, 0);
}

void Player::update(const gef::SonyController* controller_, gef::Keyboard* keyboard_) {
	//Used to only allow the transformation,
	//calculations to only happen if the player has moved.
	bool update = false;

	if (keyboard_->IsKeyDown(gef::Keyboard::KC_W)) { //Move up
		pos_->set_y(pos_->y() - speed);

		update = true;
	} else if (keyboard_->IsKeyDown(gef::Keyboard::KC_S)) { //Move down.
		pos_->set_y(pos_->y() + speed);

		update = true;
	}

	if (keyboard_->IsKeyDown(gef::Keyboard::KC_A)) { //Move to the right.
		pos_->set_x(pos_->x() + speed);

		update = true;
	} else if (keyboard_->IsKeyDown(gef::Keyboard::KC_D)) { //Move to the left.
		pos_->set_x(pos_->x() - speed);

		update = true;
	}

	//Only update the transformation,
	//if the player has moved.
	if (update) {
		gef::Matrix44 t;
		t.Rotation(gef::Quaternion(0, 0, 0, 1));
		t.SetTranslation(gef::Vector4(pos_->x(), pos_->y(), pos_->z(), 0));

		set_transform(t);
	}
}

void Player::render(gef::Renderer3D* renderer_) {
	renderer_->DrawMesh(*this);
}
