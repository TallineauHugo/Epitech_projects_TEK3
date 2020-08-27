#include "GameOverScreen.hpp"
#include <iostream>

#include "WindowManager.hpp"
#include "InputManager.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"

GameOverScreen::GameOverScreen(OtterEngine::Engine *oe) : _oe(oe)
{
	oe->_mm.stop();
	oe->_mm.loadMusicFile("ressources/music/Game over.wav");
	oe->_mm.play();

	/* Title Screen Background */
	OtterEngine::FixedSprite *bg = new OtterEngine::FixedSprite;
	bg->loadSpriteFromFile("ressources/background/BgTitle.jpg");
        bg->setPosition({1000,540});
	// OtterEngine::SpritesManager::getInstance()->addSprite(0, bg);

	/* Title Screen Text */
	sf::Font font;
	std::string str = "Press start to continue";
	font.loadFromFile("ressources/font/arial.ttf");
	_text = new OtterEngine::TextSprite;
	_text->setFont(font);
	_text->setColor(sf::Color::White);
	_text->setString(str);
	WindowManager *window = WindowManager::getInstance();
	sf::Vector2u vec = window->getSize();
	_text->setPosition({(double)vec.x / 2.5 - str.size(), (double)vec.y / 1.5});
	_text->setFontSize(40);
	OtterEngine::SpritesManager::getInstance()->addSprite(10, _text);

	/* Title Screen Text */
	str = "Game Over";
	_text2 = new OtterEngine::TextSprite;
	_text2->setFont(font);
	_text2->setColor(sf::Color::White);
	_text2->setString(str);
	vec = window->getSize();
	_text2->setPosition({(double)vec.x / 2.4 - str.size(), (double)vec.y / 2.3});
	_text2->setFontSize(40);
	OtterEngine::SpritesManager::getInstance()->addSprite(10, _text2);

	whileOnIt();
}

GameOverScreen::~GameOverScreen() {}

void GameOverScreen::whileOnIt() {
        WindowManager *window = WindowManager::getInstance();

        InputManager *inputManager = InputManager::getInstance();
	sf::Color color(sf::Color::White);
	int changing = 1;
	int blk = 0;

	while (window->isOpen()) {
		sf::Event event;
		blk++;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (inputManager->isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
			break;
		}
		if (inputManager->isKeyPressed(sf::Keyboard::Space)) {
			OtterEngine::SpritesManager::getInstance()->removeSprite(_text);
			OtterEngine::SpritesManager::getInstance()->removeSprite(_text2);
			_oe->_mm.stop();
			_oe->_mm.loadMusicFile("ressources/music/Title_screen.wav");
			_oe->_mm.play();
			return;
		}
		if (blk % 3 == 0) {
			if (color.a < 1 || color.a > 254)
				changing *= -1;
			color.a = color.a + changing;
			_text->setColor(color);
		}
		window->clear();
		_oe->update();
		window->display();
	}
}
