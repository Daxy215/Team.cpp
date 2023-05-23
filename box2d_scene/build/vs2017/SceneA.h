#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>

#include <graphics/font.h>
#include <graphics/sprite_renderer.h>

class Entity;

class SceneA {
public:
	SceneA(std::string name);
	~SceneA();

	virtual void onLoad() {}
	virtual void onUnLoad() {}
	virtual void update() {}
	virtual void render() {}
	virtual void drawHUD(gef::SpriteRenderer* sprite_renderer_, gef::Font* font_) {}
public:
	std::string name;
	std::vector<Entity*> entities;
};

#endif // !SCENE_H
