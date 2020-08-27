//
// EPITECH PROJECT, 2018
// pocketDungeon
// File description:
// input manager
//

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <map>

//#include <Windows.h>
//#include <Xinput.h>

#define STICKS_MAGIC_NUMBER 32768.0f

enum input {
	UP,
	DOWN,
	LEFT,
	RIGHT//, ...
};

class InputManager
{
public:
	static InputManager *getInstance() {
		static InputManager instance;

		return &instance;
	}
	~InputManager();

	void update();
	//clavier
	void addAction(int id, sf::Keyboard::Key key);
	bool isActionTriggered(int id);
	bool isKeyPressed(sf::Keyboard::Key key);

	//manette
	//bool isButtonPressed(WORD button);
//	sf::Vector2f getStickLeft();
//	sf::Vector2f getStickRight();
private:
	InputManager();
	std::map<int, sf::Keyboard::Key> _mActions;

//	XINPUT_STATE _currentState{};
};
