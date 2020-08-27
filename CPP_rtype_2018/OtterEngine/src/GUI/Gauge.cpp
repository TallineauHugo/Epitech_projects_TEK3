#include <iostream>
#include "Gauge.hpp"

OtterEngine::Gauge::Gauge(std::string filename, Vector2d pos, int layer, Vector2d size, int &data, int min, int max): _data(data), _min(min), _max(max)
{
	SpritesManager *spritesManager = SpritesManager::getInstance();

	setPos(pos);
	_size = size;

	_outline = new FixedSprite(this);
	_fill = new FixedSprite();

	_outline->loadSpriteFromFile(filename, {0, 0, 300, 63});
	_fill->loadSpriteFromFile(filename, {0, 63, 300, 63});

	_outline->setSize(_size);
	_outline->setPosition(pos);
	_fill->setSize({_size.x * _data / _max + _min, _size.y});
	_fill->setPosition(pos);

	spritesManager->addSprite(layer, _outline);
	spritesManager->addSprite(layer, _fill);
}

Vector2d OtterEngine::Gauge::getSize()
{
	return this->_size;
}

void OtterEngine::Gauge::update()
{
	_fill->setPosition(getPos());
	_fill->setSize({_size.x * _data / _max + _min, _size.y});
}