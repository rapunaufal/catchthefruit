#include "GameObject.h"

GameObject::GameObject(){}
GameObject::~GameObject(){}
Player::Player() {}
Player::~Player() {}
Fruit::Fruit() {}
Fruit::~Fruit() {}
Text::Text() {}
Text::~Text() {}
Background::Background() {}
Background::~Background() {}
Heart::Heart(){}
Heart::~Heart(){}

void Player::setYpost(float Nypos) {	ypos = Nypos;}
void Player::setXpost(float Nxpos) {	xpos = Nxpos;}

float Player::getXpos() {	return xpos;}
float Player::getYpos() {	return ypos;}
float Player::getFrameWidth() {	return frame_width;}
float Player::getFrameHeight() {	return frame_height;}

void Fruit::setYpost(float Nypos) {	ypos = Nypos;}
void Fruit::setXpost(float Nxpos) {	xpos = Nxpos;}
void Fruit::setXVelocity(float xVelo) {	xVelocity = xVelo;}

float Fruit::getXpos() {	return xpos;}
float Fruit::getYpos() {	return ypos;}
float Fruit::getFrameWidth() {	return frame_width;}
float Fruit::getFrameHeight() {	return frame_height;}
float Fruit::getXVelocity() {	return xVelocity;}

GLuint Text::getProgram() {	return this->program;}
void Text::setProgram(){ this->program = teksture.BuildShader("shader.vert", "shader.frag"); }

//bool Fruit::IsCollided(Player A) {
//
//	return (xpos < A.getXpos() + A.getFrameWidth() && xpos + frame_width > A.getXpos() && ypos < A.getYpos() + A.getFrameHeight() && A.getYpos() + frame_height > A.getYpos());
//}

void Heart::setVisibility(bool visi) {
	visibility = visi;
}
bool Heart::getVisibility() {
	return visibility;
}

void Heart::DrawHeart() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Activate shader
	teksture.UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 1);
	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void Heart::BuildHeart(int GetScreenWidth, int GetScreenHeight, const char *namaheart, float pos) {
	this->program = teksture.BuildShader("crateSprite.vert", "spriteAnim.frag");
	teksture.UseShader(this->program);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image(namaheart, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = (float)width;
	frame_height = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.10f, 1.10f, 1.10f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.10f, 1.10f, 1.10f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.10f, 1.10f, 1.10f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.10f, 1.10f, 1.10f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(1); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth), static_cast<GLfloat>(GetScreenHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

	
	xpos = pos;
	ypos = 0;
}


void Background::DrawBackground() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Activate shader
	teksture.UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 0);
	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Background::BuildBackground(int GetScreenWidth, int GetScreenHeight, const char *namabg) {

	this->program = teksture.BuildShader("crateSprite.vert", "spriteAnim.frag");
	teksture.UseShader(this->program);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image(namabg, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = (float)width;
	frame_height = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.10f, 1.10f, 1.10f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.10f, 1.10f, 1.10f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.10f, 1.10f, 1.10f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.10f, 1.10f, 1.10f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(1); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth), static_cast<GLfloat>(GetScreenHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));


	xpos = 0;
	ypos = 0;
}


void Fruit::DrawSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Activate shader
		teksture.UseShader(this->program);
		glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 1);
		mat4 model;
		// Translate sprite along x-axis
		model = translate(model, vec3(xpos, ypos, 0.0f));
		// Scale sprite 
		model = scale(model, vec3(frame_width, frame_height, 1));
		glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

		// Draw sprite
		glBindVertexArray(VAO);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
		glDisable(GL_BLEND);
}

void Fruit::BuildSprite(int GetScreenWidth, int GetScreenHeight, const char *fruit, float speed) {

		
	this->program = teksture.BuildShader("crateSprite.vert", "spriteAnim.frag");
	teksture.UseShader(this->program);
		
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
		
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image(fruit, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
		
	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = (float)width;
	frame_height = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};
		
	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};
		
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
		
	glBindVertexArray(VAO);
		
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
		
	glBindVertexArray(0); // Unbind VAO
		
	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth), static_cast<GLfloat>(GetScreenHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));
		
	// set sprite position, gravity, velocity
	int random_integer;
	for (int index = 0; index < 1; index++) {
		random_integer = (rand() % (GetScreenWidth / 100)) * 100;
	}
	xpos =(float) random_integer;
	//xposfruit1 = (GetScreenWidth() - frame_width2) / 4;
	ypos = 0;
	gravity = 0.05f;
	xVelocity = speed;
}



void Player::UpdateSpriteAnim(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime;

	if (walk_anim && frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx == NUM_FRAMES - 1) frame_idx = 0;  else frame_idx++;

		// Pass frameIndex to shader
		teksture.UseShader(this->program);
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
	}
}

void Player::ControlPlayerSprite(float deltaTime,InputManager inputmanager, int GetScreenWidth)
{
	walk_anim = false;

	if (inputmanager.IsKeyDown("Move Right")) {
		if (xpos + 1 + (469/NUM_FRAMES) <GetScreenWidth)
		{
			xpos += deltaTime * xVelocity * 3;
		}
		flip = 0;
		walk_anim = true;
	}

	if (inputmanager.IsKeyDown("Move Left")) {
		if (xpos - 1 > 0)
		{
			xpos -= deltaTime * xVelocity * 3;
		}
		flip = 1;
		walk_anim = true;
	}

	//if (inputmanager.IsKeyDown("Jump")) {
	//	if (onGround) {
	//		yVelocity = -12.0f;
	//		onGround = false;
	//	}
	//}

	//if (inputmanager.IsKeyUp("Jump")) {
	//	if (yVelocity < -6.0f) {
	//		yVelocity = -6.0f;
	//	}
	//}

	//yVelocity += gravity * deltaTime;
	//ypos += deltaTime * yVelocity;

	//if (ypos > yposGround) {
	//	ypos = yposGround;
	//	yVelocity = 0;
	//	onGround = true;
	//}


}

void Player::DrawPlayerSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Activate shader
	teksture.UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 1);
	//UseShader(this->program);

	// set flip
	glUniform1i(glGetUniformLocation(this->program, "flip"), flip);
	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));


	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

InputManager Player::BuildPlayerSprite(int GetScreenWidth, int GetScreenHeight, InputManager inputmanager)
{
	this->program = teksture.BuildShader("spriteAnim.vert", "spriteAnim.frag");
	//this->program = BuildShader("spriteAnim.vert", "spriteAnim.frag");

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program, "n");
	teksture.UseShader(this->program);
	//UseShader(this->program);
	glUniform1f(location, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("jo_kanan.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width) / NUM_FRAMES;
	frame_height = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.10f, 1.10f, 1.10f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.10f, 1.10f, 1.10f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.10f, 1.10f, 1.10f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.10f, 1.10f, 1.10f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth), static_cast<GLfloat>(GetScreenHeight), 0.0f, -1.0f, 1.0f);
	teksture.UseShader(this->program);
	//UseShader(this->program);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos = (GetScreenWidth - frame_width) / 2;
	yposGround = GetScreenHeight - frame_height;
	ypos = yposGround;
	gravity = 0.05f;
	xVelocity = 0.1f;

	// Add input mapping
	// to offer input change flexibility you can save the input mapping configuration in a configuration file (non-hard code) !
	inputmanager.InputMapping("Move Right", SDLK_RIGHT);
	inputmanager.InputMapping("Move Left", SDLK_LEFT);
	inputmanager.InputMapping("Move Right", SDLK_d);
	inputmanager.InputMapping("Move Left", SDLK_a);
	inputmanager.InputMapping("Move Right", SDL_BUTTON_RIGHT);
	inputmanager.InputMapping("Move Left", SDL_BUTTON_LEFT);
	inputmanager.InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	inputmanager.InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	inputmanager.InputMapping("Quit", SDLK_ESCAPE);
	inputmanager.InputMapping("Jump", SDLK_SPACE);
	inputmanager.InputMapping("Jump", SDL_CONTROLLER_BUTTON_A);
	return inputmanager;
}


void Text::InitText() {
	// Init Freetype

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		teksture.Err("ERROR::FREETYPE: Could not init FreeType Library");
	}
	FT_Face face;
	if (FT_New_Face(ft, FONTNAME, 0, &face)) {
		teksture.Err("ERROR::FREETYPE: Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, FONTSIZE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL,
		GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//this->program = teksture.BuildShader("shader.vert", "shader.frag");


	
}

void Text::RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color, int GetScreenWidth, int GetScreenHeight)
{

	// Activate corresponding render state
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	teksture.UseShader(this->program);

	glUniform3f(glGetUniformLocation(this->program, "ourColor"), color.x, color.y, color.z);
	glUniform1i(glGetUniformLocation(this->program, "text"), 1);
	glActiveTexture(GL_TEXTURE2);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 2);
	// Set orthographic projection
	mat4 projection;
	//new
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth), static_cast<GLfloat>(GetScreenHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));
	mat4 model;
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(VAO);

	// Iterate through all characters
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character

		GLfloat vertices[] = {
			// Positions   // Texture Coords
			xpos + w,	ypos + h,	1.0f, 1.0f, // Bottom Right
			xpos + w,	ypos,		1.0f, 0.0f, // Top Right
			xpos,		ypos,		0.0f, 0.0f, // Top Left
			xpos,		ypos + h,	0.0f, 1.0f  // Bottom Left 
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_QUADS, 0, 4);
		// Now advance cursors for next glyph (note that advance is number of 1 / 64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels(2 ^ 6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

}
