#include "Door.hpp"
#include "FixedSprite.hpp"
#include "Event.hpp"
#include <iostream>

Door::Door(Vector2d pos, int direction, Floor *floor) : Object(), _direction(direction), _floor(floor)
{
	_name += "Door::";
        _sprite = new OtterEngine::FixedSprite(this);
        if (_direction == 0) {
                _sprite->loadSpriteFromFile("ressources/texture/door.png");
                _hitbox.setSquareSize({152, 110});
        }
        else {
                _sprite->loadSpriteFromFile("ressources/texture/shrinked_door.png");
                _hitbox.setSquareSize({152, 81});
        }
	if (_direction == 0)
		_hitbox.setAngle(0);
	if (_direction == 1)
		_hitbox.setAngle(270);
	if (_direction == 2)
		_hitbox.setAngle(0);
	if (_direction == 3)
		_hitbox.setAngle(90);

	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
        this->setPos(pos);
        _hitbox.setType(OtterEngine::Hitbox::SQUARE);
        addEvent<Door>(_events, OtterEngine::Event<Door>("Collide", &Door::collideReaction, &Door::collideVerification));
}

int Door::collideReaction(OtterEngine::Engine *oe)
{
        std::vector<OtterEngine::Object *> objList = oe->getObjs();
        Vector2d vec;

        if (_direction == 0)
                vec = {900, 950};
        else if (_direction == 1)
                vec = {290, 500};
        else if (_direction == 2)
                vec = {900, 150};
        else
                vec = {1650, 500};
        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getIsPlayer())
                        objList[i]->setPos(vec);
                if (objList[i]->getName().find("Player") != std::string::npos)
                        objList[i]->setPos(vec);
        }
        _floor->getCurrentRoomObj()->clearRoom();
        _floor->getCurrentRoomObj()->getRoomByDirection(_direction)->enter();
        _floor->setCurrentRoom(atoi(_floor->getCurrentRoomObj()->getRoomByDirection(_direction)->getName().c_str()));
}

bool Door::collideVerification(OtterEngine::Engine *oe)
{
        std::vector<OtterEngine::Object *> objList = oe->getObjs();

        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getName().find("Player") != std::string::npos)
                        return _hitbox.doCollide(objList[i]->getHitbox());
        }
        return false;
}

void Door::updateEvents(OtterEngine::Engine *oe)
{
        for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
