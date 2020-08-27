#include "MainMenu.hpp"
#include "OtterEngine.hpp"
#include "WindowManager.hpp"
#include "InputManager.hpp"
#include <iostream>
#include "MenuManager.hpp"

#define CURSOR_X 700

MainMenu::MainMenu(OtterEngine::Engine *oe) : _actualMenu(Menus::MAIN), _cursorPos(0), _quit(false), _oe(oe) {
	MenuManager::getInstance()->getTitleScreenInstance(oe);
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("Up", &MainMenu::UpReaction, &MainMenu::UpVerification));
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("Down", &MainMenu::DownReaction, &MainMenu::DownVerification));
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("Enter", &MainMenu::EnterReaction, &MainMenu::EnterVerification));

	sf::Font font;
        font.loadFromFile("ressources/font/arial.ttf");
        _cursor = new OtterEngine::TextSprite;
        _cursor->setFont(font);
        _cursor->setColor(sf::Color::White);
        _cursor->setString("*");
        _cursor->setFontSize(40);
        displayMenu();
        whileOnIt();
}

MainMenu::~MainMenu()
{}

void MainMenu::modifyCursorPos()
{
        Vector2d pos;

	pos.x = CURSOR_X;
	pos.y = _cursorY[_cursorPos];
	_cursor->setPosition(pos);

	_textList.push_back(_cursor);
	OtterEngine::SpritesManager::getInstance()->removeSprite(_cursor);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _cursor);
}

void MainMenu::whileOnIt() {

        WindowManager *window = WindowManager::getInstance();

        InputManager *inputManager = InputManager::getInstance();

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (inputManager->isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
			break;
		}
		if (IsQuitTrue()) {
			for (int i = 0; i < _textList.size(); i++)
				OtterEngine::SpritesManager::getInstance()->removeSprite(_textList[i]);
			_textList.clear();
			return;
		}
        	window->clear();
		_oe->update();
		updateEvents(_oe);
		window->display();
	}
}

void MainMenu::displayMenu()
{
        sf::Font font;
	font.loadFromFile("ressources/font/arial.ttf");
	_cursorPos = 0;

	_cursorY.clear();
        if (_actualMenu == Menus::MAIN) {
		WindowManager *window = WindowManager::getInstance();
		sf::Vector2u vec = window->getSize();

		/*
		** TEXT 1
		*/
		std::string str = "PLAY";
		OtterEngine::TextSprite *text = new OtterEngine::TextSprite;

		text->setFont(font);
                text->setColor(sf::Color::White);
                text->setString(str);
                text->setFontSize(40);
		text->setPosition({(double)vec.x / 2.5 + str.size(), (double)vec.y / 3});

		_cursorY.push_back((double)vec.y / 3 + 5);
		_textList.push_back(text);

		/*
		** TEXT 2
		*/
		str = "OPTION";
		text = new OtterEngine::TextSprite;

		text->setFont(font);
                text->setColor(sf::Color::White);
                text->setString(str);
                text->setFontSize(40);
		text->setPosition({(double)vec.x / 2.5 + str.size() + 10, (double)vec.y / 2});

		_cursorY.push_back((double)vec.y / 2 + 5);
		_textList.push_back(text);

		/*
		** TEXT 3
		*/
		str = "EXIT";
                text = new OtterEngine::TextSprite;

                text->setFont(font);
                text->setColor(sf::Color::White);
                text->setString(str);
                text->setFontSize(40);
		text->setPosition({(double)vec.x / 2.5 + str.size() + 40, (double)vec.y / 1.50});

		_cursorY.push_back((double)vec.y / 1.5 + 5);
                _textList.push_back(text);

                for (int i = 0; i < _textList.size(); i++)
                        OtterEngine::SpritesManager::getInstance()->addSprite(1, _textList[i]);
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
		for (int i = 0; i < _textList.size(); i++)
			OtterEngine::SpritesManager::getInstance()->addSprite(1, _textList[i]);
        }
	modifyCursorPos();
}

bool MainMenu::UpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

bool MainMenu::NoUpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

int MainMenu::UpReaction(OtterEngine::Engine *oe)
{
	_cursorPos--;
	if (_cursorPos < 0)
		_cursorPos = _cursorY.size() - 1;
	modifyCursorPos();

	oe->_sm.addSound("ressources/sounds/Menu/Move menu.wav");
	removeEvent(_events, "Up");
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("NoUp", &MainMenu::NoUpReaction, &MainMenu::NoUpVerification));
	return 0;
}

int MainMenu::NoUpReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "NoUp");
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("Up", &MainMenu::UpReaction, &MainMenu::UpVerification));
	return 0;
}

bool MainMenu::EnterVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Return);
}

bool MainMenu::NoEnterVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Return);
}

int MainMenu::EnterReaction(OtterEngine::Engine *oe)
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
		MenuManager::getInstance()->getTitleScreenInstance(_oe);
		displayMenu();
	}
	removeEvent(_events, "Enter");
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("NoEnter", &MainMenu::NoEnterReaction, &MainMenu::NoEnterVerification));
	return 0;
}

int MainMenu::NoEnterReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "NoEnter");
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("Enter", &MainMenu::EnterReaction, &MainMenu::EnterVerification));
	return 0;
}

bool MainMenu::DownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

bool MainMenu::NoDownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

int MainMenu::DownReaction(OtterEngine::Engine *oe)
{
	_cursorPos++;
	if (_cursorPos > (_cursorY.size() - 1))
		_cursorPos = 0;
	modifyCursorPos();
	oe->_sm.addSound("ressources/sounds/Menu/Move menu.wav");
	removeEvent(_events, "Down");
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("NoDown", &MainMenu::NoDownReaction, &MainMenu::NoDownVerification));
	return 0;
}

int MainMenu::NoDownReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "NoDown");
	addEvent<MainMenu>(_events, OtterEngine::Event<MainMenu>("Down", &MainMenu::DownReaction, &MainMenu::DownVerification));
	return 0;
}

void MainMenu::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

void MainMenu::quit() {
	_quit = true;
}

bool MainMenu::IsQuitTrue() {
	return _quit;
}
