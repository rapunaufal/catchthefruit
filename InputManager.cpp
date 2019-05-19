#include "InputManager.h"

InputManager::InputManager() {
}
InputManager::~InputManager() {
}

void InputManager::OpenGameController()
{
	if (SDL_NumJoysticks() > 0) {
		if (SDL_IsGameController(0))
		{
			controller = SDL_GameControllerOpen(0);
			if (controller != nullptr)cout << "Game Controller is Detected" << endl;
		}
	}
}
void InputManager::CloseGameController()
{
	if (controller != nullptr) {
		SDL_GameControllerClose(0);
		cout << "Game Controller is Removed" << endl;
	}
}

// -------------- Input Handling --------------------


void InputManager::PressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = true;
	}

}

void InputManager::ReleaseKey(unsigned int keyID) {
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = false;
	}
}

void InputManager::SetMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputManager::IsKeyDown(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(name);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool InputManager::IsKeyUp(string name) {
	// Check if it is pressed this frame, and wasn't pressed last frame
	if (IsKeyDown(name) == true && WasKeyDown(name) == false) {
		return true;
	}
	return false;
}

bool InputManager::WasKeyDown(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _previousKeyMap.find(name);
	if (it != _previousKeyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

void InputManager::InputMapping(string mappingName, unsigned int keyId)
{
	_mapNames.insert(pair<unsigned int, string>(keyId, mappingName));
}