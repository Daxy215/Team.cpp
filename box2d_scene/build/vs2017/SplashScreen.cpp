#include "SplashScreen.h"
#include <input/touch_input_manager.h>

#include <system/debug_log.h>

#include <SceneManager.h>

void SplashScreen::onLoad()
{
}

void SplashScreen::onUnLoad() {

}

void SplashScreen::update() {
	timer += 0.05f;

	if (timer > 8) {
		SceneManager::loadScene("MainMenu");
	}
}

void SplashScreen::render() {

}

void SplashScreen::drawHUD(gef::SpriteRenderer* sprite_renderer_, gef::Font* font_) {
	if (font_) {
		font_->RenderText(sprite_renderer_, gef::Vector4(300, 250.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Welcome to Legless Chronicles!");
	}
}