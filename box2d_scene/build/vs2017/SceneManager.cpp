#include "SceneManager.h"

std::vector<SceneA*> SceneManager::scenes;
SceneA* SceneManager::currentActiveScene;

void SceneManager::addScene(std::string name) {
	SceneA* sceneA = new SceneA(name);
	scenes.push_back(sceneA);
}

void SceneManager::addScene(SceneA* scene) {
	scenes.push_back(scene);
}

void SceneManager::loadScene(SceneA* scene) {
	if(currentActiveScene != nullptr)
		currentActiveScene->onUnLoad();

	currentActiveScene = scene;
	
	scene->onLoad();
}

void SceneManager::loadScene(std::string sceneName) {
	for (int i = 0; i < scenes.size(); i++)
		if (scenes[i]->name._Equal(sceneName.c_str()))
			loadScene(scenes[i]);
}