#include "Credits.h"
void Credits::onLoad()
{

}

void Credits::onUnLoad()
{
}

void Credits::update() {
	y += 0.5f;
}

void Credits::render()
{
}

void Credits::drawHUD(gef::SpriteRenderer* sprite_renderer_, gef::Font* font_) {
	// 960, 544
	font_->RenderText(sprite_renderer_, gef::Vector4(15, (544 / 2) - y, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "This is credits testing pokdwADFIWAJDFOIADFOVAMCFODCOVIAZPZOCVKPOAZK!");
}
