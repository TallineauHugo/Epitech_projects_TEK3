#include "Shop.hpp"
#include "FixedSprite.hpp"
#include "Hitbox.hpp"
#include <iostream>

Shop::Shop(Vector2d pos, Vector2d size) : Object()
{
	_name += "Shop::";
        _sprite = new OtterEngine::FixedSprite(this);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
        _sprite->loadSpriteFromFile("ressources/texture/shop.png");
        this->setPos(pos);
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(size);
}
