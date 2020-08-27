#include <iostream>
#include "Player.hpp"
#include "MonsterGenerator.hpp"
#include "ScrollingCamera.hpp"
#include "ShootingEnnemy.hpp"
#include "ZigZagEnnemy.hpp"
#include "WindowManager.hpp"
#include "InputManager.hpp"
#include "OtterEngine.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"

int main()
{
	OtterEngine::Engine oe;
	oe.addObject(new Player (Vector2d(0, 0)));
	oe.addObject(new ShootingEnnemy (Vector2d(2500, 200)));
	oe.addObject(new ShootingEnnemy (Vector2d(2500, 500)));
	oe.addObject(new ZigZagEnnemy (Vector2d(2000, 300)));
	oe.addObject(new ZigZagEnnemy (Vector2d(2400, 600)));
	oe.addObject(new ZigZagEnnemy (Vector2d(2900, 900)));

	WindowManager *window = WindowManager::getInstance();
	window->setView(sf::Vector2f(window->getSize().x/ 2,window->getSize().y / 2), sf::Vector2f(window->getSize().x, window->getSize().y));
	oe.addObject(new ScrollingCamera(window->getView()));
	while (window->isOpen())
	{
		window->clear();
		oe.update();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		window->display();
	}

}
