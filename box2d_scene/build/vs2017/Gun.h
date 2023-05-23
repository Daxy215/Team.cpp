#ifndef GUN_H
#define GUN_H

#include <Entity.h>

class Gun : public Entity {
public:
	Gun(std::string name_, PrimitiveBuilder& builder_, b2World& world_, gef::Vector4* position_, gef::Quaternion* rotation_,
		gef::Vector4* scale_)
		: Entity(name_, builder_, world_, position_, rotation_, scale_) {
		createMesh();
	}

	virtual void updatePhysics();
};

#endif // !GUN_H
