#include "Entity.h"

#include <MathA.h>
#include <maths/quaternion.h>
#include <maths/math_utils.h>

Entity::Entity(std::string name_, PrimitiveBuilder& builder_, b2World& world_,
	gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_) : name_(name_), builder_(builder_), world_(world_), position_(position_), rotation_(rotation_), scale_(scale_) {

}

Entity::~Entity() {
	position_ = NULL;
	delete position_;
	
	rotation_ = NULL;
	delete rotation_;

	scale_ = NULL;
	delete scale_;

	body_ = NULL;
}

void Entity::init(b2BodyType bodyType_) {
	gef::Vector4 size = (*scale_) * 0.5f;
	createMesh();
	
	b2BodyDef body_def;
	body_def.type = bodyType_;
	body_def.position = b2Vec2(position_->x(), position_->y());

	body_ = world_.CreateBody(&body_def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x(), size.y());

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 1.0f;

	body_->CreateFixture(&fixture_def);

	setUserData();
}

void Entity::init(b2BodyDef body_def) {
	b2PolygonShape shape;
	shape.SetAsBox(scale_->x() * 0.5f, scale_->y() * 0.5f);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 1.0f;

	init(body_def, fixture_def);
}

void Entity::init(b2FixtureDef fixture_, b2BodyType bodyType_) {
	b2BodyDef body_def;
	body_def.type = bodyType_;
	body_def.position = b2Vec2(position_->x(), position_->y());

	init(body_def, fixture_);
}

void Entity::init(b2BodyDef body_def, b2FixtureDef fixture_) {
	createMesh();

	body_ = world_.CreateBody(&body_def);
	body_->CreateFixture(&fixture_);

	setUserData();
}