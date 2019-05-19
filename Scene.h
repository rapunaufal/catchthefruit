#ifndef SCENE_H
#define SCENE_H

#include "Demo.h"
#include "Menu.h"


class Scene{

private:
	enum SCREENS
	{
		menu, ingame
	};
	SCREENS CurrentScreen;
public:
	Scene();
	~Scene();
	static void Relese();
	virtual void Render();
	virtual void Update();
	Menu menunya;
	Demo ingamenya;
	bool ngecekScene = true;
	
private:
	Engine::Game &game = Menu();
	//Engine::Game &game = Demo();
	


};

#endif