#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SceneA.h>

#include <string>

class SplashScreen : public SceneA {
public:
	SplashScreen(std::string name) : SceneA(name) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
};

#endif // !SPLASHSCREEN_H