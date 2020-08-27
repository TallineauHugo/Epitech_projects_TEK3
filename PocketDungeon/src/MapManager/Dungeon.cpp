#include <iostream>
#include <cstdlib>
#include "time.h"
#include "Types.hpp"
#include "Dungeon.hpp"
#include "Wall.hpp"

Dungeon::Dungeon(int level, OtterEngine::Engine *oe) : _level(level), _currentFloor(0), _oe(oe)
{
        srand(time(NULL));

        std::cout << "We create a dungeon level " << _level << std::endl;
	int tmp;

	tmp = rand() % 6;
	if (tmp == 0)
		_theme = Fire;
	else if (tmp == 1)
		_theme = Water;
	else if (tmp == 2)
		_theme = Leaf;
	else
		_theme = Normal;
	std::cout << "Dungeon Type = " << _theme << std::endl;
        _nbFloor = rand() % 3 + (level * 2);
        std::cout << "There is " << _nbFloor << " floor(s)" << std::endl;

        for (int i = 0; i < _nbFloor; i++) {
                Floor *floor = new Floor(_level, oe, i, this);
                _floorList.push_back(floor);
        }
	if (_theme != Normal) {
		_themeSprite = new OtterEngine::FixedSprite;
		if (_theme == Fire)
			_themeSprite->loadSpriteFromFile("ressources/texture/Fire_theme.png");
		else if (_theme == Water)
			_themeSprite->loadSpriteFromFile("ressources/texture/Water_theme.png");
		else if (_theme == Leaf)
			_themeSprite->loadSpriteFromFile("ressources/texture/Leaf_theme.png");
		_themeSprite->setSize(Vector2d(5000, 3000));
		OtterEngine::SpritesManager::getInstance()->addSprite(3, _themeSprite);
	}
        else
                _themeSprite = nullptr;

        enterCurrentFloor();
}

Dungeon::~Dungeon()
{
        std::cout << "We destroy a dungeon" << std::endl;

        while (_floorList.size() > 0) {
                delete _floorList.back();
                _floorList.pop_back();
        }

}

void Dungeon::enterCurrentFloor(void)
{
        for (int i = 0; i < _floorList.size(); i++) {
                if (i == _currentFloor)
                        _floorList[i]->enterCurrentRoom();
	}
}

void Dungeon::setCurrentFloor(int currentFloor) {
        _floorList[_currentFloor]->getCurrentRoomObj()->clearRoom();
        if (currentFloor >= _floorList.size()) {
                ExitDungeon();
                return;
        }
        _currentFloor = currentFloor;
        _floorList[_currentFloor]->enterCurrentRoom();
}

int Dungeon::getCurrentFloor(void) const {
        return _currentFloor;
}

void Dungeon::goToNextFloor(void) {
        if (getCurrentFloor() < _floorList.size())
                setCurrentFloor(getCurrentFloor() + 1);
        else {
                _ended = true;
	OtterEngine::SpritesManager::getInstance()->removeSprite(_themeSprite);
	delete(_themeSprite);
	}
}

void Dungeon::ExitDungeon(void) {
        std::cout << "You finished the dungeon " << std::endl;
        std::vector<OtterEngine::Object *> objList = _oe->getObjs();
        Vector2d vec = {500, 500};

        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getIsPlayer()) {
                        objList[i]->setPos(vec);
                }
                if (objList[i]->getName().find("Player") != std::string::npos)
                        objList[i]->setPos(vec);
        }
        if (_themeSprite)
                OtterEngine::SpritesManager::getInstance()->removeSprite(_themeSprite);
        delete(_themeSprite);
        HUBFactory::getInstance()->createHUB(_oe);
        return;
}
