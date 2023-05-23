#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SceneA.h>

#include <input/keyboard.h>
#include <input/input_manager.h>

#include <string>

class SplashScreen : public SceneA {
public:
	SplashScreen(std::string name, gef::InputManager* input_manager_) : SceneA(name) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
	virtual void drawHUD(gef::SpriteRenderer* sprite_renderer_, gef::Font* font_);

public:
	float timer = 0;
public:
	gef::InputManager* input_manager_;
};

#endif // !SPLASHSCREEN_H