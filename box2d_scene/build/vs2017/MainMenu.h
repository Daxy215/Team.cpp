#ifndef MAINMENU_H
#define MAINMENU_H

#include <SceneA.h>

#include <maths/vector2.h>
#include <graphics/sprite.h>
#include <input/keyboard.h>
#include <input/input_manager.h>
#include <system/debug_log.h>

#include <vector>

#include <string>

struct Button {
	Button(std::string text, gef::Vector2 offset, gef::Vector2* position, gef::Vector2* size) {
		this->text = text;
		this->offset = offset;

		sprite.set_position(position->x, position->y, 0.0f);
		sprite.set_width(size->x);
		sprite.set_height(size->y);
	}

	std::string text;

	gef::Vector2 offset;
	gef::Sprite sprite;

	void (*callback)(); // Function pointer type for the callback
};

class MainMenu : public SceneA {
public:
	MainMenu(std::string name, gef::InputManager* input_manager_) : SceneA(name), input_manager_(input_manager_) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
	virtual void drawHUD(gef::SpriteRenderer* sprite_renderer_, gef::Font* font_);
public:
	gef::InputManager* input_manager_;

	std::vector<Button*> buttons;
};

#endif // !MAINMENU_H