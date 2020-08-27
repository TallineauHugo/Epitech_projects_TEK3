#include "InGameMenu.hpp"
#include "OtterEngine.hpp"
#include "WindowManager.hpp"
#include "InputManager.hpp"
#include <iostream>
#include <unistd.h>
#include "MenuManager.hpp"

int newGame(OtterEngine::Engine *oe);

#define CURSOR_X 700

InGameMenu::InGameMenu(OtterEngine::Engine *oe) : _actualMenu(Menus::MAIN), _cursorPos(0), _quit(false), _oe(oe) {

	oe->pause();
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Up", &InGameMenu::UpReaction, &InGameMenu::UpVerification));
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Down", &InGameMenu::DownReaction, &InGameMenu::DownVerification));
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Enter", &InGameMenu::EnterReaction, &InGameMenu::EnterVerification));
        // addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Pause", &InGameMenu::PauseReaction, &InGameMenu::PauseVerification));

	sf::Font font;
        font.loadFromFile("ressources/font/arial.ttf");
        _cursor = new OtterEngine::TextSprite;
        _cursor->setFont(font);
        _cursor->setColor(sf::Color::White);
        _cursor->setString("*");
        _cursor->setFontSize(40);

        _bgMenu = new OtterEngine::FixedSprite;
        OtterEngine::SpritesManager::getInstance()->addSprite(10, _bgMenu);
        _bgMenu->setPosition({900, 550});
        _bgMenu->loadSpriteFromFile("ressources/sprites/gui/Menu.png");

        displayMenu();
        whileOnIt();
}

InGameMenu::~InGameMenu()
{}

std::string InGameMenu::getName() {
	return "Menu";
}
void InGameMenu::modifyCursorPos()
{
        Vector2d pos = (Vector2d)_cursor->getPosition();

	pos.x = CURSOR_X;
	pos.y = _cursorY[_cursorPos];
	_cursor->setPosition(pos);
	_textList.push_back(_cursor);
	OtterEngine::SpritesManager::getInstance()->removeSprite(_cursor);
	OtterEngine::SpritesManager::getInstance()->addSprite(11, _cursor);
}

void InGameMenu::whileOnIt() {
        WindowManager *window = WindowManager::getInstance();

        InputManager *inputManager = InputManager::getInstance();

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (inputManager->isKeyPressed(sf::Keyboard::Escape) || IsQuitTrue()) {
			_cursorY.clear();
			for (int i = 0; i < _textList.size(); i++)
				OtterEngine::SpritesManager::getInstance()->removeSprite(_textList[i]);
			OtterEngine::SpritesManager::getInstance()->removeSprite(_bgMenu);
			_oe->pause();
			return;
		}
        	window->clear();
		_oe->update();
		updateEvents(_oe);
		window->display();
	}
}

void InGameMenu::displayMenu()
{
        sf::Font font;
	font.loadFromFile("ressources/font/arial.ttf");
	_cursorPos = 0;

	_cursorY.clear();
        if (_actualMenu == Menus::MAIN) {
                std::string str = "PLAY";
                std::string str2 = "OPTION";
                std::string str3 = "EXIT";
                OtterEngine::TextSprite *text = new OtterEngine::TextSprite;
                OtterEngine::TextSprite *text2 = new OtterEngine::TextSprite;
                OtterEngine::TextSprite *text3 = new OtterEngine::TextSprite;
                text->setFont(font);
                text->setColor(sf::Color::White);
                text->setString(str);
                text->setFontSize(40);
                text2->setFont(font);
                text2->setColor(sf::Color::White);
                text2->setString(str2);
                text2->setFontSize(40);
                text3->setFont(font);
                text3->setColor(sf::Color::White);
                text3->setString(str3);
                text3->setFontSize(40);

                WindowManager *window = WindowManager::getInstance();
                sf::Vector2u vec = window->getSize();
		_cursorY.push_back((double)vec.y / 3 + 5);
		_cursorY.push_back((double)vec.y / 2 + 5);
		_cursorY.push_back((double)vec.y / 1.5 + 5);
                text->setPosition({(double)vec.x / 2.5 + str.size(), (double)vec.y / 3});
                text2->setPosition({(double)vec.x / 2.5 + str2.size() + 10, (double)vec.y / 2});
                text3->setPosition({(double)vec.x / 2.5 + str3.size() + 40, (double)vec.y / 1.50});
                _textList.push_back(text);
                _textList.push_back(text2);
                _textList.push_back(text3);
                for (int i = 0; i < _textList.size(); i++)
                        OtterEngine::SpritesManager::getInstance()->addSprite(11, _textList[i]);
        }
        else if (_actualMenu == Menus::PLAY) {

        }
        else if (_actualMenu == Menus::OPTION) {
                std::string str = "RETURN";
		WindowManager *window = WindowManager::getInstance();
		sf::Vector2u vec = window->getSize();

                OtterEngine::TextSprite *text = new OtterEngine::TextSprite;
		text->setFont(font);
		text->setColor(sf::Color::White);
		text->setString(str);
		text->setFontSize(40);

		_cursorY.push_back((double)vec.y / 3 + 5);
		text->setPosition({(double)vec.x / 2.5 + str.size(), (double)vec.y / 3});

		_textList.push_back(text);
		for (int i = 0; i < _textList.size(); i++) {
			std::cout << "Add sprite" << std::endl;
			OtterEngine::SpritesManager::getInstance()->addSprite(11, _textList[i]);
		}

        }
	modifyCursorPos();
}

bool InGameMenu::UpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

bool InGameMenu::NoUpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

int InGameMenu::UpReaction(OtterEngine::Engine *oe)
{
	_cursorPos--;
	if (_cursorPos < 0)
		_cursorPos = _cursorY.size() - 1;
	oe->_sm.addSound("ressources/sounds/Menu/Move menu.wav");
	modifyCursorPos();
	removeEvent(_events, "Up");
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("NoUp", &InGameMenu::NoUpReaction, &InGameMenu::NoUpVerification));
	return 0;
}

int InGameMenu::NoUpReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "NoUp");
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Up", &InGameMenu::UpReaction, &InGameMenu::UpVerification));
	return 0;
}

bool InGameMenu::EnterVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Return);
}

bool InGameMenu::NoEnterVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Return);
}

int InGameMenu::EnterReaction(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _textList.size(); i++) {
		OtterEngine::SpritesManager::getInstance()->removeSprite(_textList[i]);
	}
	_textList.clear();
	if (_actualMenu == Menus::MAIN && _cursorPos == 0) {
		quit();
	}
	else if ((_actualMenu == Menus::MAIN && _cursorPos == 1) || (_actualMenu == Menus::OPTION && _cursorPos == 0)) {
		if (_actualMenu == Menus::MAIN)
			_actualMenu = Menus::OPTION;
		else
			_actualMenu = Menus::MAIN;
		displayMenu();
	}
	else if (_actualMenu == Menus::MAIN && _cursorPos == (_cursorY.size() - 1)) {
		std::cout << "back to title screen" << std::endl;
		oe->clearEngine();
		oe->restart();
		quit();
		// newGame(oe);
		// MenuManager::getInstance()->getMainMenuInstance();

	}
	removeEvent(_events, "Enter");
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("NoEnter", &InGameMenu::NoEnterReaction, &InGameMenu::NoEnterVerification));
	return 0;
}

int InGameMenu::NoEnterReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "NoEnter");
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Enter", &InGameMenu::EnterReaction, &InGameMenu::EnterVerification));
	return 0;
}

bool InGameMenu::DownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

bool InGameMenu::NoDownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

int InGameMenu::DownReaction(OtterEngine::Engine *oe)
{
	_cursorPos++;
	if (_cursorPos > (_cursorY.size() - 1))
		_cursorPos = 0;
	oe->_sm.addSound("ressources/sounds/Menu/Move menu.wav");
	modifyCursorPos();
	removeEvent(_events, "Down");
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("NoDown", &InGameMenu::NoDownReaction, &InGameMenu::NoDownVerification));
	return 0;
}

int InGameMenu::NoDownReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "NoDown");
	addEvent<InGameMenu>(_events, OtterEngine::Event<InGameMenu>("Down", &InGameMenu::DownReaction, &InGameMenu::DownVerification));
	return 0;
}

void InGameMenu::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

void InGameMenu::quit() {
	_quit = true;
}

bool InGameMenu::IsQuitTrue() {
	return _quit;
}
