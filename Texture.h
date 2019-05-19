#ifndef TEXTURE_H
#define TEXTURE_H

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

using namespace std;
using namespace glm;
class Texture
{
public:
	Texture();
	~Texture();
	GLuint BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void UseShader(GLuint program);
	void Err(string errorString);
	int a;
private:
	void CheckShaderErrors(GLuint shader, string type);

};

#endif