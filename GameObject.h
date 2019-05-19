#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include "Texture.h"
#include "InputManager.h"

#define NUM_FRAMES 6
#define FRAME_DUR 80
#define NUM_OBJECT 2
#define FONTSIZE 40
#define FONTNAME "hongkonghustle.ttf"

using namespace std;
using namespace glm;

struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};
class GameObject
{
public:
	GameObject();
	~GameObject();
	void BuildSprite(int GetScreenWidth, int GetScreenHeight);
	//InputManager BuildPlayerSprite(int GetScreenWidth, int GetScreenHeight, InputManager inputmanager);
	void DrawPlayerSprite();

	//void UpdateSpriteAnim(float deltaTime);
	//void ControlPlayerSprite(float deltaTime, InputManager inputmanager);
	Texture teksture;

//protected:
	float frame_width = 0, frame_height = 0;
	float frame_dur = 0, xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0;//, yposGround = 0;
	GLuint VBO, VAO, EBO, texture, program;
	//bool walk_anim = false, onGround = true;
	//unsigned int frame_idx = 0, flip = 0;

};
class Heart :GameObject {
public :
	Heart();
	~Heart();

	void DrawHeart();
	void BuildHeart(int GetScreenWidth, int GetScreenHeight, const char *namaheart, float pos);
	void setVisibility(bool visi);
	bool getVisibility();

private:
	bool visibility = true;
};
class Text :GameObject {
public:
	Text();
	~Text();
	void InitText();
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color, int GetScreenWidth, int GetScreenHeight);
	void setProgram();
	GLuint getProgram();
private :
	map<GLchar, Character> Characters;
};

class Background:GameObject {
public:
	Background();
	~Background();
	void DrawBackground();
	void BuildBackground(int GetScreenWidth, int GetScreenHeight, const char *namabg);
};

class Fruit:GameObject {
public:
	Fruit();
	~Fruit();

	void BuildSprite(int GetScreenWidth, int GetScreenHeight, const char *fruit, float speed);
	void DrawSprite();
	float getXpos();
	float getYpos();
	float getFrameWidth();
	float getFrameHeight();
	float getXVelocity();
	void setYpost(float Nypos);
	void setXpost(float Nxpos);
	void setXVelocity(float xVelo);
	//bool IsCollided(Player A);
};

class Player:GameObject {
public:
	Player();
	~Player();
	InputManager BuildPlayerSprite(int GetScreenWidth, int GetScreenHeight, InputManager inputmanager);
	void ControlPlayerSprite(float deltaTime, InputManager inputmanager, int GetScreenWidth);
	void UpdateSpriteAnim(float deltaTime);
	void DrawPlayerSprite();
	float getXpos();
	float getYpos();
	float getFrameWidth();
	float getFrameHeight();
	void setYpost(float Nypos);
	void setXpost(float Nxpos);
	//float getXpos();
	//float getYpos();
	//float getFrameWidth();
	//float getFrameHeight();
	

private:
	float yposGround = 0;
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;

};
#endif