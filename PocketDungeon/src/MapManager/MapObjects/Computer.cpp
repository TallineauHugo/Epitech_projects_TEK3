#include "Computer.hpp"
#include "FixedSprite.hpp"
#include "Hitbox.hpp"
#include <iostream>

Computer::Computer(Vector2d pos, Vector2d size) : Object()
{
        _name += "Computer::";
        _sprite = new OtterEngine::FixedSprite(this);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
        _sprite->loadSpriteFromFile("ressources/texture/computer.png");
        this->setPos(pos);
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(size);
}
