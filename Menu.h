#ifndef MENU_H
#define MENU_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Texture.h"
#include "Demo.h"
#include "GameObject.h"

using namespace glm;

#define FONTSIZE 40
#define FONTNAME "hongkonghustle.ttf"
#define NUM_BUTTON 2

struct Character2 {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Menu :
	public Engine::Game
{
public:
	Menu();
	~Menu();
	virtual void Init();
	virtual void DeInit();
	virtual void Update(float deltaTime);
	virtual void Render();
	Texture teksture;
	Background bg_menu;
	bool getcek();
	void setCek();
	Fruit pisang;
private:
	bool cekpencet = false;
	void InitText();
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	void InitButton();
	void RenderButton();
	map<GLchar, Character2> Characters;
	GLuint texture[NUM_BUTTON], hover_texture[NUM_BUTTON], VBO, VBO2, VAO, VAO2, program;
	float button_width[NUM_BUTTON], button_height[NUM_BUTTON], hover_button_width[NUM_BUTTON], hover_button_height[NUM_BUTTON];
	int activeButtonIndex = 0;
};
#endif

