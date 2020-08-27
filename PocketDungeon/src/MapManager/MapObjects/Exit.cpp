#include "Exit.hpp"
#include "FixedSprite.hpp"
#include "Dungeon.hpp"
#include "Event.hpp"
#include <iostream>

Exit::Exit(Vector2d pos, Dungeon *dungeon) : Object(), _dungeon(dungeon)
{
	_name += "Exit::";
        _sprite = new OtterEngine::FixedSprite(this);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
        std::cout << "On create une exit at " << pos.x << ";" << pos.y << std::endl;
        _sprite->loadSpriteFromFile("ressources/texture/Exit.png");
        this->setPos(pos);
        _hitbox.setType(OtterEngine::Hitbox::SQUARE);
        _hitbox.setSquareSize({150, 50});
        addEvent<Exit>(_events, OtterEngine::Event<Exit>("Collide", &Exit::collideReaction, &Exit::collideVerification));
}


int Exit::collideReaction(OtterEngine::Engine *oe) {
        _dungeon->goToNextFloor();
}

bool Exit::collideVerification(OtterEngine::Engine *oe)
{
        std::vector<OtterEngine::Object *> objList = oe->getObjs();

        for (size_t i = 0; i != objList.size(); i++) {
                if (objList[i]->getName().find("Player") != std::string::npos)
                        return _hitbox.doCollide(objList[i]->getHitbox());
        }
        return false;
}

void Exit::updateEvents(OtterEngine::Engine *oe)
{
        for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

void Exit::useExit(void) {
        _dungeon->goToNextFloor();
}
