#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/box2d.h>

#include <input/keyboard.h>
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>

namespace gef {
	class Renderer3D;
}

class Entity : public gef::MeshInstance {
public:
	Entity(std::string name_, PrimitiveBuilder& builder_, b2World& world_,
	gef::Vector4* position_, gef::Quaternion* rotation_, gef::Vector4* scale_);

	~Entity();

	virtual void update() {
		updatePhysics();
	}
	
	virtual void render(gef::Renderer3D* renderer_3d_) { }

	virtual void processInput(gef::InputManager* input_manager_) {  }
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
	std::string getName() { return name_; }
	
	gef::Vector4* getPosition() { return position_; }
	gef::Vector4* setPosition(gef::Vector4* position_) { this->position_ = position_; return position_; }

	gef::Quaternion* getRotation() { return rotation_; }
	gef::Vector4* getScale() { return scale_; }
	gef::Vector4* setScale(gef::Vector4* scale_) { this->scale_ = scale_; return scale_; }

	b2Body* getBody() { return body_; }
public:
	bool active;
private:
	void setUserData() { body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(this); }
protected:
	std::string name_;

	gef::Vector4* position_, *scale_;
	gef::Quaternion* rotation_;
	gef::Matrix44 transform_;

	b2Body* body_ = nullptr;

	PrimitiveBuilder& builder_;
	b2World& world_;
};

#endif //ENTITY_H
