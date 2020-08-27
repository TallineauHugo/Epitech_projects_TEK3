#include "TextSprite.hpp"
#include "WindowManager.hpp"

#include <iostream>

void OtterEngine::TextSprite::setString(std::string str)
{
	this->_text.setString(str);
}

void OtterEngine::TextSprite::setFont(sf::Font font)
{
	this->_font = font;
	this->_text.setFont(this->_font);
}

sf::FloatRect OtterEngine::TextSprite::getBounds() const
{
	return this->_text.getGlobalBounds();
}

void OtterEngine::TextSprite::setOrigin(sf::Vector2f origin)
{
	this->_text.setOrigin(origin);
}

void OtterEngine::TextSprite::setOrigin(float posX, float posY)
{
	this->_text.setOrigin(posX, posY);
}

void OtterEngine::TextSprite::setColor(sf::Color color)
{
	this->_text.setFillColor(color);
}

void OtterEngine::TextSprite::setFontSize(unsigned int size)
{
	this->_text.setCharacterSize(size);
}

void OtterEngine::TextSprite::refresh()
{
	Vector2d objSize;
	Vector2d objPos;

	if (this->_obj) {
		objSize = this->_obj->getSize();
		this->setSize({objSize.x, objSize.y});
		this->_text.setOrigin(objSize.x / 2 + this->getBounds().width / 2, objSize.y / 2 + this->getBounds().height / 2);
		objPos = this->_obj->getPos();
		this->setPosition({objPos.x + objSize.x / 2, objPos.y + objSize.y / 2});
	}
	WindowManager::getInstance()->draw(this->_text);
}

bool OtterEngine::TextSprite::loadSpriteFromFile(std::string filename)
{
	(void)filename;
	return false;
}

bool OtterEngine::TextSprite::loadSpriteFromFile(std::string filename, sf::IntRect area)
{
	(void)filename;
	(void)area;
	return false;
}

void OtterEngine::TextSprite::setPosition(Vector2d pos)
{
	this->_text.setPosition(pos.x, pos.y);
}

sf::Vector2i OtterEngine::TextSprite::getPosition() const
{
	return sf::Vector2i(this->_text.getPosition());
}

void OtterEngine::TextSprite::setSize(Vector2d size)
{
	(void)size;
}