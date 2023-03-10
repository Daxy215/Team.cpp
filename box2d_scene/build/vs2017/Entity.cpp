#include "Entity.h"

Entity::Entity(PrimitiveBuilder& builder_, b2World& world_,
	gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_,
	b2FixtureDef fixture_) : builder_(builder_), world_(world_), position_(position_), rotation_(rotation_), scale_(scale_) {

	init(fixture_);
}

Entity::~Entity() {
	position_ = NULL;
	delete position_;

	
}

void Entity::init(b2FixtureDef fixture_) {
	set_mesh(builder_.GetDefaultCubeMesh());

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(position_->x(), position_->y());

	body_ = world_.CreateBody(&body_def);

	//b2PolygonShape player_shape;
	//player_shape.SetAsBox(scale_->x() * 0.5f, scale_->y() * 0.5f);

	//b2FixtureDef player_fixture_def;
	//player_fixture_def.shape = &player_shape;
	//player_fixture_def.density = 1.0f;

	body_->CreateFixture(&fixture_);
}

void Entity::update() {
	gef::Matrix44 player_transform;
	player_transform.SetIdentity();

	gef::Matrix44 rotationZ;
	rotationZ.SetIdentity();
	rotationZ.RotationZ(body_->GetAngle());

	gef::Matrix44 player_translation;
	player_translation.SetIdentity();
	player_translation.SetTranslation(gef::Vector4(body_->GetPosition().x, body_->GetPosition().y, 0));

	player_transform = rotationZ * player_translation;
	set_transform(player_transform);
}