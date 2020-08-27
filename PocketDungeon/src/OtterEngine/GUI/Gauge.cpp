#include <iostream>
#include "Gauge.hpp"

OtterEngine::Gauge::Gauge(std::string outline, std::string fill, Vector2d pos, int layer, Vector2d size, int& data, int min, int& max): _data(data), _min(min), _max(max), _layer(layer)
{
	SpritesManager *spritesManager = SpritesManager::getInstance();

	setPos(pos);
	_size = size;

	_outline = new FixedSprite();
	_fill = new FixedSprite();

	_outline->loadSpriteFromFile(outline);
	_fill->loadSpriteFromFile(fill);

	_outline->setSize(_size);
	_outline->setPosition(pos);

	float ratio = ((_max <= 0) ? 0.f : (float)_data / (float)_max);
	_fill->setSize(Vector2d((_size.x * ratio), _size.y));
	_fill->setPosition(pos);

	spritesManager->addSprite(layer + 1, _outline);
	spritesManager->addSprite(layer, _fill);
}

OtterEngine::Gauge::~Gauge()
{
	this->hide();
}

void OtterEngine::Gauge::show()
{
	SpritesManager *spritesManager = SpritesManager::getInstance();

	spritesManager->addSprite(_layer + 1, _outline);
	spritesManager->addSprite(_layer, _fill);
}

void OtterEngine::Gauge::hide()
{
	SpritesManager *spritesManager = SpritesManager::getInstance();

	spritesManager->removeSprite(_outline);
	spritesManager->removeSprite(_fill);
}

Vector2d OtterEngine::Gauge::getSize()
{
	return this->_size;
}

void OtterEngine::Gauge::update()
{
	float ratio = ((_max <= 0) ? 0.f : (float)_data / (float)_max);
	Vector2d pos = getPos();
	Vector2d size;

	size.x = (int)(_size.x * ratio);
	size.y = (int)(_size.y);
	
	_outline->setPosition(pos);
	pos.x = pos.x - (_size.x * (1 - ratio)) / 2;
	_fill->setPosition(pos);

	_fill->setSize(size);
}