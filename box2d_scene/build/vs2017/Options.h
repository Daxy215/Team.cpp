#ifndef OPTIONS_H
#define OPTIONS_H

#include <SceneA.h>

#include <system/platform.h>
#include <string>

#include <gef.h>

#include <graphics/sprite.h>
#include <assets/png_loader.h>
#include <graphics/texture.h>

class Options : public SceneA {
public:
	Options(std::string name, gef::Platform& platform_) : SceneA(name), platform_(platform_) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
public:
	gef::Platform& platform_;
private:
	float fadeIn, fadeOut;
};

#endif // !OPTIONS_H