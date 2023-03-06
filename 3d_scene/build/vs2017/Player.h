#pragma once
#include <system/platform.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <graphics/mesh_instance.h>
#include <maths/quaternion.h>
#include "primitive_builder.h"
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>
#include <input/keyboard.h>

class Player : public gef::MeshInstance {
public:
	Player();

	void init(PrimitiveBuilder* builder_);
	void update(const gef::SonyController* controller_, gef::Keyboard* keyboard_);
	void render(gef::Renderer3D* renderer_);
public:
	float speed = 0.5f;

	gef::Vector4* pos_;
};

