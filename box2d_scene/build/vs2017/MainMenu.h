#ifndef MAINMENU_H
#define MAINMENU_H

#include <SceneA.h>

#include <string>

class MainMenu : public SceneA {
public:
	MainMenu(std::string name) : SceneA(name) {}

	virtual void onLoad();
	virtual void onUnLoad();
	virtual void update();
	virtual void render();
};

#endif // !MAINMENU_H