#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>

class Entity;

class SceneA {
public:
	SceneA(std::string name);
	~SceneA();

	virtual void onLoad() {}
	virtual void onUnLoad() {}
	virtual void render() {}
	virtual void update() {}
public:
	std::string name;
	std::vector<Entity*> entities;
};

#endif // !SCENE_H
