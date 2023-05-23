#include "Player.h"

#include <system/debug_log.h>
#include <graphics/material.h>
#include <input/touch_input_manager.h>
#include <maths/quaternion.h>
#include "box2d/box2d.h"

#include <Windows.h>

void Player::initA() {
	float scale = 0.5f;

	b2PolygonShape bullet_shape;
	bullet_shape.SetAsBox(scale / 2, scale / 2);

	b2FixtureDef bullet_fixture_def;
	bullet_fixture_def.shape = &bullet_shape;
	bullet_fixture_def.density = 0.5f;

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(0, 0);

	//body_def.bullet = true;
	//body_def.fixedRotation = true;

	for (int i = 0; i < poolSize; i++) {
		Entity* entity = new Entity("Bullets", builder_, world_, new gef::Vector4(0, 0, 0, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
		entity->init(body_def);

		entity->active = false;
		entity->setScale(new gef::Vector4(scale, scale, scale, 1));

		bulletPool[i] = entity;
	}

	gun = new Gun("Gun", builder_, world_, new gef::Vector4(0, 2, 0, 2), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
}

void Player::update() {
	updatePhysics();

	for (int i = 0; i < poolSize; i++) {
		if (bulletPool[i]->active) {
			bulletPool[i]->update();
		}
	}
}

void Player::render(gef::Renderer3D* renderer_3d_) {
	const gef::MeshInstance* mesh = static_cast<gef::MeshInstance*>(gun);
	renderer_3d_->DrawMesh(*mesh);

	for (int i = 0; i < poolSize; i++) {
		if (bulletPool[i]->active) {
			Entity* entity = bulletPool[i];

			const gef::MeshInstance* mesh = static_cast<gef::MeshInstance*>(entity);
			renderer_3d_->DrawMesh(*mesh);
		}
	}
}

void Player::processInput(gef::InputManager* input_manager_) {
	if (input_manager_->keyboard()->IsKeyDown(input_manager_->keyboard()->KC_LEFT)) {
		gunAngle += 0.05f;
	} else if (input_manager_->keyboard()->IsKeyDown(input_manager_->keyboard()->KC_RIGHT)) {
		gunAngle -= 0.05f;
	}

	//gun->getRotation()->z = gunAngle;
	rotation_->z = gunAngle;

	//Shoot
	if (input_manager_->keyboard()->IsKeyDown(input_manager_->keyboard()->KC_SPACE)) {
		if (shootingTimer > 2) {
			shootingTimer = 0;

			bulletPool[shootIndex]->active = true;
			bulletPool[shootIndex]->getBody()->SetTransform(b2Vec2(position_->x(), position_->y()), gunAngle);

			float bulletForceMagnitude = 350.0f; // Adjust this value as needed
			b2Vec2 angle = b2Vec2(cos(gunAngle), sin(gunAngle));
			b2Vec2 bulletForce = bulletForceMagnitude * angle;
			bulletPool[shootIndex]->getBody()->ApplyForceToCenter(bulletForce, true);
			
			body_->ApplyForceToCenter(b2Vec2((-angle.x) * 1000, (-angle.y) * 1000), true);

			shootIndex++;

			if (shootIndex >= poolSize)
				shootIndex = 0;
		}
	}

	shootingTimer += 0.05;
}

void Player::createMesh() {
	gef::Vector4 size = (*scale_) * 0.5f;
	
	set_mesh(builder_.CreateBoxMesh(size));
	
}

void Player::damage(int damage) {
	health = health - damage;

	if (health >= 0) {
		//dies (dont know if this goes here)
	}
}

void Player::heal(int healing) {
	health = min(maxhealth, health + healing);
}
