#ifndef OPTIONS_H
#define OPTIONS_H

#include <SceneA.h>

#include <string>

class Options : public SceneA {
public:
	Options(std::string name) : SceneA(name) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
private:
	float fadeIn, fadeOut;
};

#endif // !OPTIONS_H