#include "TitleScreen.hpp"
#include <iostream>

#include "WindowManager.hpp"
#include "InputManager.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"

TitleScreen::TitleScreen(OtterEngine::Engine *oe) : _oe(oe)
{
	oe->_mm.stop();
	oe->_mm.loadMusicFile("ressources/music/Pkm Opening Theme.wav");
	oe->_mm.play();

	/* Title Screen Background */
	OtterEngine::FixedSprite *bg = new OtterEngine::FixedSprite;
	bg->loadSpriteFromFile("ressources/background/BgTitle.jpg");
        bg->setPosition({1000,540});
	// OtterEngine::SpritesManager::getInstance()->addSprite(0, bg);

	/* Title Screen Text */
	sf::Font font;
	std::string str = "Press start to play";
	font.loadFromFile("ressources/font/arial.ttf");
	_text = new OtterEngine::TextSprite;
	_text->setFont(font);
	_text->setColor(sf::Color::White);
	_text->setString(str);
	WindowManager *window = WindowManager::getInstance();
	sf::Vector2u vec = window->getSize();
	_text->setPosition({(double)vec.x / 2.5 - str.size(), (double)vec.y / 1.5});
	_text->setFontSize(40);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _text);

        whileOnIt();
}

TitleScreen::~TitleScreen() {}

void TitleScreen::whileOnIt() {
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
