#include "Scene.h"

Scene::Scene()
{
	CurrentScreen = menu;
	game.Start("User Interface Menu", 800, 600, false, WindowFlag::WINDOWED, 60, 1);
}


Scene::~Scene()
{
}

void Scene::Update() {

	switch (CurrentScreen)
	{
	
	case menu:

		if (ngecekScene)
		{
			static int frameCounter = 0;
			frameCounter++;

			if (frameCounter == 150) {

				frameCounter = 0;
			}
			Engine::Game &game = Demo();
			game.Start("Catch the Fruit", 800, 600, false, WindowFlag::WINDOWED, 60, 1);
			//game.cek = false;
			ngecekScene = false;
			CurrentScreen = ingame;
		}
		break;
	case ingame:
		
		if (!ngecekScene)
		{
			static int frameCounter = 0;
			frameCounter++;

			if (frameCounter == 150) {

				frameCounter = 0;
			}
			Engine::Game &game = Menu();
			game.Start("User Interface Menu", 800, 600, false, WindowFlag::WINDOWED, 60, 1);
			//game.cek = true;
			ngecekScene = true;
			CurrentScreen = menu;
		}
		break;
	}
}

int main(int argc, char** argv) {
	Scene a;
	int j = 0;
	while (j<1)
	{
		a.Update();
	}
	return 0;
}
void Scene::Render() {

}