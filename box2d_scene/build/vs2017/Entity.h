#ifndef ENTITY_H
#define ENTITY_H

#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/box2d.h>

class Entity : public gef::MeshInstance {
public:
	Entity(PrimitiveBuilder& builder_, b2World& world_,
	gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_);

	~Entity();

	void update();

	gef::Matrix44 getTransform() { return transform_; }
public:
	void init(b2BodyType bodyType_);
	void init(b2BodyDef body_def);
	void init(b2FixtureDef fixture_, b2BodyType bodyType_);
	void init(b2BodyDef body_def, b2FixtureDef fixture_);
public: //Getters / Setters
	gef::Vector4* getPosition() { return position_; }
	gef::Quaternion* getRotation() { return rotation_; }
	gef::Vector4* getScale() { return scale_; }
private:
	gef::Vector4* position_, *scale_;
	gef::Quaternion* rotation_;
	gef::Matrix44 transform_;

	b2Body* body_;

	PrimitiveBuilder& builder_;
	b2World& world_;
};

#endif //ENTITY_H
