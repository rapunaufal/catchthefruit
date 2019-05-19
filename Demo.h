#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Texture.h"
#include "GameObject.h"
#include "AudioManager.h"
#include "Menu.h"

#define NUM_FRAMES 6
#define FRAME_DUR 80
//#define NUM_OBJECT 2

using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	float frame_width = 0, frame_height = 0;
	Texture teksture = Texture();
	Player player;
	Fruit pisang, pisang2, pisang3;
	Fruit cherry, cherry2;
	Fruit orange;
	Fruit bomb,bomb2,bomb3;
	Background bg;
	Text text;
	AudioManager audio;
	void play();
	Heart hati1, hati2, hati3,
		  hatikosong1, hatikosong2,hatikosong3;

private:
	bool first = true;
	int lives = 3, score = 0;
	string hasilscore;
	bool isCollided(Player a, Fruit b);
	//GLuint texture[NUM_OBJECT];
	//float frame_dur = 0, xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	//GLuint VBO, VAO, EBO, texture, program;
	//bool walk_anim = false, onGround = true;
	//unsigned int frame_idx = 0, flip = 0;
	//void BuildPlayerSprite();
	//void DrawPlayerSprite();
	//void UpdateSpriteAnim(float deltaTime);
	//void ControlPlayerSprite(float deltaTime);
};
#endif

