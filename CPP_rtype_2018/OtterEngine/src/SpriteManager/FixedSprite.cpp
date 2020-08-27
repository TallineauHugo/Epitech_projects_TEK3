#include <iostream>

#include "FixedSprite.hpp"
#include "WindowManager.hpp"

bool OtterEngine::FixedSprite::loadSpriteFromFile(std::string filename)
{
	if (!_texture.loadFromFile(filename))
		return false;
	this->_texture.setRepeated(true);
	_sprite.setTexture(_texture);
	this->_pos = {0, 0};
	this->_size = {(double)_texture.getSize().x, (double)_texture.getSize().y};
	return true;
}

bool OtterEngine::FixedSprite::loadSpriteFromFile(std::string filename, sf::IntRect area)
{
	if (!_texture.loadFromFile(filename, area))
		return false;
	this->_texture.setRepeated(true);
	_sprite.setTexture(_texture);
	this->_size = {(double)area.width, (double)area.height};
	this->_pos = {(double)area.left, (double)area.top};
	return true;
}

void OtterEngine::FixedSprite::refresh()
{
	Vector2d objSize;
	Vector2d objPos;

	if (this->_obj) {
		objSize = this->_obj->getSize();
		_sprite.setOrigin(objSize.x / 2 / _sprite.getScale().x, objSize.y / 2 / _sprite.getScale().y);
		objPos = this->_obj->getPos();
		this->setSize({objSize.x, objSize.y});
		this->setPosition({objPos.x, objPos.y});
		this->setRotation(this->_obj->getAngle());
	}
	else
		_sprite.setOrigin(this->_size.x / 2 / _sprite.getScale().x, this->_size.y / 2 / _sprite.getScale().y);
	WindowManager::getInstance()->draw(this->_sprite);
}

void OtterEngine::FixedSprite::setPosition(Vector2d pos)
{
	this->_sprite.setPosition(pos.x, pos.y);
	this->_pos = pos;
}

void OtterEngine::FixedSprite::setSize(Vector2d size)
{
	double scaleXFactor = size.x / this->_sprite.getLocalBounds().width;
	double scaleYFactor = size.y / this->_sprite.getLocalBounds().height;

	this->_sprite.setScale(scaleXFactor, scaleYFactor);
	this->_size = {scaleXFactor * this->_sprite.getLocalBounds().width, scaleYFactor * this->_sprite.getLocalBounds().height};
}

void OtterEngine::FixedSprite::setRepeated(bool b)
{
	this->_texture.setRepeated(b);
}

sf::Vector2i OtterEngine::FixedSprite::getPosition() const
{
	sf::Vector2f pos = this->_sprite.getPosition();

	return {(int)pos.x, (int)pos.y};
}

void OtterEngine::FixedSprite::setRotation(int angle)
{
	this->_sprite.setRotation(angle);
}
