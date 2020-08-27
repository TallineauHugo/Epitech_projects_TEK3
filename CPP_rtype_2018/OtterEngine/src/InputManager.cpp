//
// EPITECH PROJECT, 2018
// pocketDungeon
// File description:
// inputManager
//

//#include <minwinbase.h>

#include "InputManager.hpp"

InputManager::InputManager()
{}

InputManager::~InputManager()
{}

void InputManager::update()
{
//	ZeroMemory(&_currentState, sizeof(XINPUT_STATE));
//	XInputGetState(0, &_currentState);
}

void InputManager::addAction(int id, sf::Keyboard::Key key)
{
	_mActions[id] = key;
}

bool InputManager::isActionTriggered(int id)
{
	return sf::Keyboard::isKeyPressed(_mActions[id]);
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

/*bool InputManager::isButtonPressed(WORD button)
{
	return (_currentState.Gamepad.wButtons & button) != 0;
	}*/

/*sf::Vector2f InputManager::getStickLeft()
{
	sf::Vector2f res;

	res.x = _currentState.Gamepad.sThumbLX;
	res.y = -float(_currentState.Gamepad.sThumbLY);

	res.x /= STICKS_MAGIC_NUMBER;
	res.y /= STICKS_MAGIC_NUMBER;

	if (abs(res.x) < 0.19f)
		res.x = 0;
	if (abs(res.y) < 0.19f)
		res.y = 0;
	
	return res;
}*/

 /*sf::Vector2f InputManager::getStickRight()
{
	sf::Vector2f res;

	res.x = _currentState.Gamepad.sThumbRX;
	res.y = -float(_currentState.Gamepad.sThumbRY);

	res.x /= STICKS_MAGIC_NUMBER;
	res.y /= STICKS_MAGIC_NUMBER;

	if (abs(res.x) < 0.19f)
		res.x = 0;
	if (abs(res.y) < 0.19f)
		res.y = 0;
	
	return res;
	}*/
