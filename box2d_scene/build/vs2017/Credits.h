#ifndef CREDITS_H

#include <SceneA.h>

#include <string>

class Credits : public SceneA {
public:
	Credits(std::string name) : SceneA(name) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
};

#endif // !CREDITS_H
