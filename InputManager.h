#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

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

class InputManager
{
public:
	InputManager();
	~InputManager();
	// Input Handling
	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	void SetMouseCoords(float x, float y);
	// Returns true if the key is held down
	bool IsKeyDown(string name);
	// Returns true if the key was just pressed
	bool IsKeyUp(string name);
	// getters
	vec2 GetMouseCoords() const { return _mouseCoords; }
	// Returns true if the key is held down
	bool WasKeyDown(string name);
	void InputMapping(string mappingName, unsigned int keyId);
	void OpenGameController();
	void CloseGameController();
	
private:
	unordered_map<unsigned int, string> _mapNames;
	unordered_map<string, bool> _keyMap;
	unordered_map<string, bool> _previousKeyMap;
	vec2 _mouseCoords;
	SDL_GameController *controller;
	//void PollInput();
};
#endif