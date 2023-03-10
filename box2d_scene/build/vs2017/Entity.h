#pragma once
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/box2d.h>

class Entity : public gef::MeshInstance {
public:
	Entity(PrimitiveBuilder& builder_, b2World& world_,
	gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_,
	b2FixtureDef fixture_);

	~Entity();

	void update();

	gef::Matrix44 getTransform() { return transform_; }
private:
	void init(b2FixtureDef fixture_);
private:
	gef::Vector4* position_, *scale_;
	gef::Quaternion* rotation_;
	gef::Matrix44 transform_;

	b2Body* body_;

	PrimitiveBuilder& builder_;
	b2World& world_;
};

