#include "Gun.h"

void Gun::updatePhysics() {
	if (body_ != nullptr)
		setPosition(new gef::Vector4(body_->GetPosition().x, body_->GetPosition().y, 0));

	gef::Matrix44 player_transform;
	player_transform.SetIdentity();

	gef::Matrix44 rotationZ;
	rotationZ.SetIdentity();
	rotationZ.RotationZ(rotation_->z);

	gef::Matrix44 scale;
	scale.SetIdentity();
	scale.Scale(*getScale());

	gef::Matrix44 player_translation;
	player_translation.SetIdentity();
	player_translation.SetTranslation(*position_);

	player_transform = rotationZ * scale * player_translation;
	set_transform(player_transform);
}