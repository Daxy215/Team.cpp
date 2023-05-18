#include "Options.h"

#include <gef.h>
#include <graphics/sprite.h>
#include <graphics/texture.h>
#include <graphics/vertex_buffer.h>

void Options::onLoad() {
	gef::PNGLoader png_loader;
	gef::ImageData* imageData;

	png_loader.Load("imagePath", platform_, *imageData);

	if (imageData != nullptr) {
		gef::Texture* texture = gef::Texture::Create(platform_, *imageData);
	}
}

void Options::onUnLoad() {

}

void Options::update() {

}

void Options::render() {

}
