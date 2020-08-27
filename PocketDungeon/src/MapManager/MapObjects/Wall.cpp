#include "Wall.hpp"
#include "FixedSprite.hpp"
#include "Hitbox.hpp"
#include "Pokemon.hpp"
#include <iostream>

Wall::Wall(Vector2d pos, Vector2d size) : Object()
{
	_name += "Wall::";
	_sprite = new OtterEngine::FixedSprite(this);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
        _sprite->loadSpriteFromFile("ressources/texture/Wall.png");
        _hitbox.setPos(pos);
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(size);
	addEvent<Wall>(_events, OtterEngine::Event<Wall>("Collide", &Wall::collideReaction, &Wall::collideVerification));
}

int Wall::collideReaction(OtterEngine::Engine *oe)
{
        std::vector<OtterEngine::Object *> objList = oe->getObjs();
        Vector2d vec;

	for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getIsPlayer()) {
			if (_hitbox.getPos().y <= 100)
				objList[i]->setPos(Vector2d(objList[i]->getPos().x, objList[i]->getPos().y + 4.25));
			else if (_hitbox.getPos().y >= 1030)
				objList[i]->setPos(Vector2d(objList[i]->getPos().x, objList[i]->getPos().y - 4.25));
			else if (_hitbox.getPos().x <= 10)
				objList[i]->setPos(Vector2d(objList[i]->getPos().x + 4.25, objList[i]->getPos().y));
			else if (_hitbox.getPos().x >= 1048)
				objList[i]->setPos(Vector2d(objList[i]->getPos().x - 4.25, objList[i]->getPos().y));
		}
        }}

bool Wall::collideVerification(OtterEngine::Engine *oe)
{
        std::vector<OtterEngine::Object *> objList = oe->getObjs();

        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getName().find("Player") != std::string::npos)
                        return _hitbox.doCollide(objList[i]->getHitbox());
        }
        return false;
}

void Wall::updateEvents(OtterEngine::Engine *oe)
{
        for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
