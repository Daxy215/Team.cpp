#ifndef ENTITY_H
#define ENTITY_H

#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/box2d.h>

#include <input/keyboard.h>
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>

class Entity : public gef::MeshInstance {
public:
	Entity(PrimitiveBuilder& builder_, b2World& world_,
	gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_);

	~Entity();

	virtual void update() {
		updatePhysics();
	}

	virtual void processInput(gef::SonyController* controller, gef::Keyboard* keyboard) {  }
	virtual void createMesh() {
		gef::Vector4 size = (*scale_) * 0.5f;
		set_mesh(builder_.CreateBoxMesh(size));
	}

	void updatePhysics();

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
	void setUserData() { body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(this); }
protected:
	gef::Vector4* position_, *scale_;
	gef::Quaternion* rotation_;
	gef::Matrix44 transform_;

	b2Body* body_;

	PrimitiveBuilder& builder_;
	b2World& world_;
};

#endif //ENTITY_H
