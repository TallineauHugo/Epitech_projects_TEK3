#include <iostream>
#include "PokemonFactory.hpp"
#include "Pokemon.hpp"
#include "WindowManager.hpp"
#include "DungeonFactory.hpp"
#include "InputManager.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"
#include "HUBFactory.hpp"
#include "Wall.hpp"
#include "OtterEngine.hpp"
#include "Player.hpp"
#include "MenuManager.hpp"
#include "ExpBag.hpp"

#include <iostream>

int newGame(OtterEngine::Engine *oe)
{
	std::cout << "______________WE START A NEW GAME________________" << std::endl;
	MenuManager::getInstance()->getMainMenuInstance(oe);


	Player *player = new Player;
	//ExpBag *expbag = new ExpBag;
	InputManager *inputManager = InputManager::getInstance();

	Pokemon *pkmn = PokemonFactory::getInstance()->createPokemon("pikachu", 10);
	Pokemon *pkmn2 = PokemonFactory::getInstance()->createPokemon("bulbasaur", 5);
	OtterEngine::FixedSprite *bg = new OtterEngine::FixedSprite;

	player->addPkmnToTeam(pkmn);
	player->addPkmnToTeam(pkmn2);

	oe->addObject(pkmn);
	oe->addObject(player);
	//oe->addObject(expbag);
	bg->loadSpriteFromFile("ressources/texture/background.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(0, bg);
	bg->setPosition({960,540});

	HUBFactory::getInstance()->createHUB(oe);

	//pkmn->displayStats();

	pkmn->setPos(Vector2d(500, 500));
	pkmn2->setPos(Vector2d(500, 500));
	//pkmn->applyStatusFor(Status::POISON, 5); //à remettre si test du Heart pour pas être full life
	//expbag->setPos(Vector2d(500, 250));


	pkmn->show();


	WindowManager *window = WindowManager::getInstance();

	if (oe->getPause())
		oe->pause();
	int ret = 0;

	while (window->isOpen()) {
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (inputManager->isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
			break;
		}

		window->clear();
		ret = oe->update();
		if (ret != 0) {
			oe->pause();
			break;
		}
		window->display();
	}
	window->clear();
	return ret;
}

int main()
{
	int ret = 1;
	srand(time(NULL));

	OtterEngine::Engine oe;

	while (ret == 1) {
		ret = newGame(&oe);
		oe.normalize();
	}
	return 0;
}
