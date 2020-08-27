#include "InvisibleWall.hpp"
#include "FixedSprite.hpp"
#include "Hitbox.hpp"
#include <iostream>

InvisibleWall::InvisibleWall(Vector2d pos, Vector2d size) : Wall(pos, size)
{
	_name += "InvisibleWall::";
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	// delete (_sprite);
        _hitbox.setPos(pos);
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(size);
}
