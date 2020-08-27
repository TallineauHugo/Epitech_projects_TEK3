#include "Portal.hpp"
#include "AnimatedSprite.hpp"
#include "DungeonFactory.hpp"
#include "Hitbox.hpp"
#include "Event.hpp"
#include "HUB.hpp"
#include <iostream>

Portal::Portal(Vector2d pos, Vector2d size, int dungeonlevel, OtterEngine::Engine *oe, HUB *hub) : Object(), _dungeonLevel(dungeonlevel), _oe(oe), _hub(hub)
{
	_name += "Portal::";
        _sprite = new OtterEngine::AnimatedSprite(this);
        _sprite->loadSpriteFromFile("ressources/animatedSprites/hub_portal.png", 16, 16, 1, 1);
        dynamic_cast<OtterEngine::AnimatedSprite *>(_sprite)->setSpeed(500);
        OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
        this->setPos(pos);
        _hitbox.setType(OtterEngine::Hitbox::SQUARE);
        _hitbox.setSquareSize(size);
        addEvent<Portal>(_events, OtterEngine::Event<Portal>("Collide", &Portal::collideReaction, &Portal::collideVerification));
}

Dungeon *Portal::launchNewDungeon(void) {
        _hub->clearHUB();
        return DungeonFactory::getInstance()->createDungeon(_dungeonLevel, _oe);
}

int Portal::collideReaction(OtterEngine::Engine *oe)
{
        Vector2d vec = {500, 250};
        std::vector<OtterEngine::Object *> objList = oe->getObjs();

	std::cout << "IT COLLIDES" << std::endl;
        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getIsPlayer()) {
                        objList[i]->setPos(vec);
                }
                if (objList[i]->getName().find("Player") != std::string::npos)
                        objList[i]->setPos(vec);
        }
        launchNewDungeon();
}

bool Portal::collideVerification(OtterEngine::Engine *oe)
{
        std::vector<OtterEngine::Object *> objList = oe->getObjs();

        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getName().find("Player") != std::string::npos) {
                        return _hitbox.doCollide(objList[i]->getHitbox());
                }
        }
        return false;
}

void Portal::updateEvents(OtterEngine::Engine *oe)
{
        for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
