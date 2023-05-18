#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <vector>

#include "SceneA.h"

class SceneManager {
public:
	static void addScene(std::string name);
	static void addScene(SceneA* scene);
	static void loadScene(SceneA* scene);
	static void loadScene(std::string sceneName);

public:
	static std::vector<SceneA*> scenes;
	static SceneA* currentActiveScene;
};

#endif // !SCENEMANAGER_H
