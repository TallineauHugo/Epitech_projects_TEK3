 #include <iostream>
#include "HUB.hpp"
#include "Wall.hpp"
#include "Shop.hpp"
#include "Portal.hpp"
#include "Computer.hpp"
#include "WindowManager.hpp"

HUB::HUB(OtterEngine::Engine *oe) : Room("HUB"), _oe(oe)
{}

HUB::~HUB() {}

void HUB::clearHUB() {
        std::cout << "On destroy tout" << std::endl;
        std::vector<OtterEngine::Object *> objs = _oe->getObjs();
        OtterEngine::Object *player;

        OtterEngine::SpritesManager *_SpriteM = OtterEngine::SpritesManager::getInstance();

        std::cout << "-----------OBJECT LIST------------" << std::endl;
        for (int i = 0; i != objs.size(); i++) {
                if ((objs[i]->getName().find("Player") != std::string::npos)) {
                        player = objs[i];
                }
                std::cout << "obj " << i << " = " << objs[i]->getName() << std::endl;
        }

        for (int i = 0; i != objs.size(); i++) {
                if (player != objs[i] && !objs[i]->getIsPlayer()) {
                        std::cout << "On destroy " << objs[i]->getName() << std::endl;
                        _oe->removeObjectById(_oe->getIndex(objs[i]));
                        _SpriteM->removeSprite(objs[i]->getSprite());
                }
                else {
                        std::cout << "On touche pas à " << objs[i]->getName() << std::endl;
                }
        }
	_oe->_mm.stop();
	_oe->_mm.loadMusicFile("ressources/music/Donjon.wav");
	_oe->_mm.play();
}

void HUB::loadHUB()
{
        int x;
        int y;
        sf::Vector2u w_size;
	int j;
	std::vector<OtterEngine::Object *> objs = _oe->getObjs();

	for (j = 0; j != objs.size(); j++) {
		if ((objs[j]->getName().find("Player") != std::string::npos)) {
			dynamic_cast<Player *>(objs[j])->updateLevel();
			break;
		}
	}
        w_size = WindowManager::getInstance()->getSize();
        for (x = 10; x < w_size.x - 10; x += 102)
                _oe->addObject(new Wall({(double)x, 100}, {100, 100}));
        for (y = 10; y < w_size.y - 100; y += 102)
                _oe->addObject(new Wall({(double)10, (double)y}, {100, 100}));
        for (int i = 10; i < w_size.x - 10; i += 102)
                _oe->addObject(new Wall({(double)i, (double)y}, {100, 100}));
        for (int i = 10; i < w_size.y - 80; i += 102)
                _oe->addObject(new Wall({(double)x - 100, (double)i}, {100, 100}));
        _oe->addObject(new Shop({250, 250}, {291, 282}));
        _oe->addObject(new Shop({1300, 250}, {291, 282}));
        _oe->addObject(new Portal({250, 800}, {100,100}, 1, _oe, this));
	if (dynamic_cast<Player *>(objs[j])->getLevel() > 0)
		_oe->addObject(new Portal({450, 800}, {100,100}, 2, _oe, this));
	if (dynamic_cast<Player *>(objs[j])->getLevel() > 2)
		_oe->addObject(new Portal({650, 800}, {100,100}, 3, _oe, this));
        _oe->addObject(new Computer({1300, 600}, {110, 100}));
	_oe->_mm.stop();
	_oe->_mm.loadMusicFile("ressources/music/Title_screen.wav");
	_oe->_mm.play();
}
