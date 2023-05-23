#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <system/debug_log.h>

#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <maths/quaternion.h>
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

	virtual void updatePhysics() {
		if(body_ != nullptr)
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

	gef::Matrix44 getTransform() { return transform_; }
public:
	void init(b2BodyType bodyType_);
	void init(b2BodyDef body_def);
	void init(b2FixtureDef fixture_, b2BodyType bodyType_);
	void init(b2BodyDef body_def, b2FixtureDef fixture_);

	void destroy() {
		gef::DebugOut("destroying %s", name_.c_str());

		active = false;
		world_.DestroyBody(body_);

		body_ = nullptr;
	}
public: //Getters / Setters
	std::string getName() { return name_; }
	
	gef::Vector4* getPosition() { return position_; }
	gef::Vector4* setPosition(gef::Vector4* position_) { this->position_ = position_; return position_; }

	gef::Quaternion* getRotation() { return rotation_; }
	gef::Quaternion* setRotation(gef::Quaternion* rotation_) { this->rotation_ = rotation_; }
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
