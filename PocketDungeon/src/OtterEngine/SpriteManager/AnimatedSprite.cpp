#include <iostream>
#include "TimeManager.hpp"
#include "AnimatedSprite.hpp"
#include "macros.hpp"

OtterEngine::AnimatedSprite::~AnimatedSprite()
{
	unsigned long i = 0;
	unsigned long size = this->_sprites.size();

	while (i < size) {
		delete this->_sprites[i];
		this->_sprites.erase(i);
		i++;
	}
}

bool OtterEngine::AnimatedSprite::loadSpriteFromFile(std::string filename, int rowRange, int rowMax, int line, int lineMax)
{
	sf::Image spritesheet;
	int speed = rowMax * 50;
	int width;
	int height;
	int i;

	if (!spritesheet.loadFromFile(filename))
		return false;
	width = spritesheet.getSize().x / rowMax;
	height = spritesheet.getSize().y / lineMax;
	for (i = 0; i < rowRange; i++) {
		this->_sprites[i] = new FixedSprite(this->_obj);
		this->_sprites[i]->loadSpriteFromFile(filename, sf::IntRect(i * width, height * (line - 1), width, height));
	}
	this->_waitedTime = 0;
	this->_currentFrame = 0;
	this->_nbFrame = rowRange;
	this->_speed = speed;
	this->_size = this->_sprites[0]->getSize();
	this->_pos = this->_sprites[0]->getSize();
	return true;
}

void OtterEngine::AnimatedSprite::refresh()
{
	Vector2d objSize;
	Vector2d objPos;

	if (this->_obj) {
		objPos = this->_obj->getPos();
		if (this->_obj->getHitbox().getType() == Hitbox::SQUARE)
			objSize = this->_obj->getHitbox().getSquareSize();
		else if (this->_obj->getHitbox().getType() == Hitbox::CIRCLE)
			objSize = {(double)this->_obj->getHitbox().getRadius() * 2, (double)this->_obj->getHitbox().getRadius() * 2};
		this->setSize({objSize.x, objSize.y});
		this->setPosition({objPos.x, objPos.y});
	}
	this->_waitedTime += TimeManager::getInstance()->getDeltaTime();
	if (this->_waitedTime >= FPS / this->_speed) {
		this->_currentFrame++;
		if (this->_currentFrame == this->_nbFrame)
			this->_currentFrame = 0;
		this->_waitedTime -= FPS / this->_speed;
	}
	this->_sprites[this->_currentFrame]->refresh();
}

void OtterEngine::AnimatedSprite::setPosition(Vector2d pos)
{
	int i = 0;

	while (i < this->_nbFrame) {
		this->_sprites[i]->setPosition(pos);
		i++;
	}
	this->_pos = pos;
}

void OtterEngine::AnimatedSprite::setSize(Vector2d size)
{
	int i = 0;

	while (i < this->_nbFrame) {
		this->_sprites[i]->setSize(size);
		i++;
	}
	this->_size = size;
}

void OtterEngine::AnimatedSprite::setSpeed(int speed)
{
	this->_speed = speed;
}

bool OtterEngine::AnimatedSprite::loadSpriteFromFile(std::string filename)
{
}

bool OtterEngine::AnimatedSprite::loadSpriteFromFile(std::string filename, sf::IntRect area)
{
}

sf::Vector2i OtterEngine::AnimatedSprite::getPosition() const
{
}