#include "SceneA.h"

#include "Entity.h"

SceneA::SceneA(std::string name) {
	this->name = name;
}

SceneA::~SceneA() {
	for (int i = 0; i < entities.size(); i++) {
		delete entities[i];
	}

	entities.clear();
}
