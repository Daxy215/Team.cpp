#include "MainMenu.h"

#include <system/debug_log.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/texture.h>
#include <input/touch_input_manager.h>
#include <graphics/colour.h>

#include <scene_app.h>

void MainMenu::onLoad() {
	// 960, 544

	buttons.push_back(new Button("Play!", gef::Vector2(-24, -20), new gef::Vector2(960 / 2, 150), new gef::Vector2(50, 50)));
	buttons.back()->callback = []() {
		SceneManager::loadScene("Level 1");
	};

	buttons.push_back(new Button("Options", gef::Vector2(-38, -20), new gef::Vector2(960 / 2, 150 + (68) + 5), new gef::Vector2(100, 55)));
	buttons.back()->callback = []() {
		SceneManager::loadScene("Options");
	};

	buttons.push_back(new Button("Credits", gef::Vector2(-38, -20), new gef::Vector2(960 / 2, 150 + (68 * 2) + 5), new gef::Vector2(100, 55)));
	buttons.back()->callback = []() {
		SceneManager::loadScene("Credits");
	};

	buttons.push_back(new Button("Quit", gef::Vector2(-24, -20), new gef::Vector2(960 / 2, 150 + (68 * 3) + 5), new gef::Vector2(50, 50)));
	buttons.back()->callback = []() {

	};
}

void MainMenu::onUnLoad() {

}

void MainMenu::update() {
	gef::Vector2 m = SceneApp::instance->mousePos;

	if (!input_manager_->touch_manager() || (input_manager_->touch_manager()->max_num_panels() <= 0))
		return;

	auto touch = input_manager_->touch_manager()->touches(0);

	const gef::TouchContainer& panel_touches = input_manager_->touch_manager()->touches(0);

	// go through the touches
	for (gef::ConstTouchIterator touch = panel_touches.begin(); touch != panel_touches.end(); ++touch) {
		for (int i = 0; i < buttons.size(); i++) {
			gef::Vector4 pos = buttons[i]->sprite.position();
			float w = buttons[i]->sprite.width();
			float h = buttons[i]->sprite.height();
			pos.set_x(pos.x() - w * 0.5f);
			pos.set_y(pos.y() - h * 0.5f);

			if (m.x > pos.x() && m.x < pos.x() + w
				&& m.y > pos.y() && m.y < pos.y() + h) {
				if (touch->type == gef::TT_ACTIVE)
					buttons[i]->callback();
			}
		}
	}
}

void MainMenu::render() {
	SceneApp::instance->getSpriteRenderer()->Begin();

	for (int i = 0; i < buttons.size(); i++) {
		SceneApp::instance->getSpriteRenderer()->DrawSprite(buttons[i]->sprite);
	}

	SceneApp::instance->getSpriteRenderer()->End();
}

void MainMenu::drawHUD(gef::SpriteRenderer* sprite_renderer_, gef::Font* font_) {
	if (!font_)
		return;
	
	for (int i = 0; i < buttons.size(); i++) {
		font_->RenderText(sprite_renderer_, gef::Vector4(buttons[i]->sprite.position().x() + buttons[i]->offset.x, buttons[i]->sprite.position().y() + buttons[i]->offset.y, -4),
			1.0f, 0xff000000, gef::TJ_LEFT, buttons[i]->text.c_str());
	}
}
