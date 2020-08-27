#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <WindowManager.hpp>
#include <fstream>

#include "Button.hpp"
#include "SpritesManager.hpp"

OtterEngine::Button::Button(std::string text, sf::Font &font, Vector2d pos, int layer, Vector2d size, Callback callback, void *data, std::string spriteNormalPath, std::string spriteHoveredPath, std::string spriteClickedPath)
{
	Vector2d textPos;
	sf::FloatRect textBounds;
	std::ifstream normalFile(spriteNormalPath);
	std::ifstream hoveredFile;
	std::ifstream clickedFile;

	_layer = layer;
	this->_size = size;
	this->setAngle(0);
	this->_offset = {_size.x / 2, _size.y / 2};

	this->setPos({pos.x, pos.y});
	if (spriteHoveredPath.empty())
		spriteHoveredPath = spriteNormalPath;
	if (spriteClickedPath.empty())
		spriteClickedPath = spriteHoveredPath;
	hoveredFile = std::ifstream(spriteHoveredPath);
	clickedFile = std::ifstream(spriteClickedPath);
	if (!normalFile.good() || !hoveredFile.good() || !clickedFile.good()) {
		std::cerr << "Sprite file missing" << std::endl;
		exit(84);
	}

	_text = new TextSprite(this);
	_normalSprite = new FixedSprite(this);
	_normalSprite->loadSpriteFromFile(spriteNormalPath);
	_hoveredSprite = new FixedSprite(this);
	_hoveredSprite->loadSpriteFromFile(spriteHoveredPath);
	_clickedSprite = new FixedSprite(this);
	_clickedSprite->loadSpriteFromFile(spriteClickedPath);
	SpritesManager::getInstance()->addSprite(layer, _normalSprite);
	SpritesManager::getInstance()->addSprite(layer + 1, _text);

	_callback = std::move(callback);
	_data = data;

	_state = NORMAL;
	_text->setString(std::move(text));
	_text->setFont(font);
	textBounds = _text->getBounds();
	_text->setOrigin(textBounds.left + this->_size.x / 2, textBounds.top + this->_size.y / 2);
	_text->setColor(sf::Color::Black);

	_normalSprite->setSize(this->_size);
	_normalSprite->setPosition(this->getPos());
	_hoveredSprite->setSize(this->_size);
	_hoveredSprite->setPosition(this->getPos());
	_clickedSprite->setSize(this->_size);
	_clickedSprite->setPosition(this->getPos());

	textPos = Vector2d(this->getPosition().x + this->_size.x / 2, this->getPosition().y + this->_size.y / 2);
	_text->setPosition(textPos);
}

OtterEngine::Button::~Button()
{
}

void OtterEngine::Button::setPosition(Vector2d pos)
{
	Vector2d textPos;

	Object::setPos(pos);
	_normalSprite->setPosition(pos);
	_hoveredSprite->setPosition(pos);
	_clickedSprite->setPosition(pos);
	//textPos = Vector2d(this->getPos().x + this->_size.x / 2, this->getPos().y + this->_size.y / 2);
	//_text->setPosition(textPos);
}

void OtterEngine::Button::setSize(Vector2d size)
{
	Vector2d textPos;

	this->_size = size;
	_normalSprite->setSize(this->_size);
	_hoveredSprite->setSize(this->_size);
	_clickedSprite->setSize(this->_size);
	textPos = Vector2d(this->getPos().x + this->_size.x / 2, this->getPos().y + this->_size.y / 2);
	_text->setPosition(textPos);
}

void OtterEngine::Button::setFontSize(unsigned int size)
{
	Vector2d textPos;
	sf::FloatRect textBounds;

	_text->setFontSize(size);
	this->setSize({_text->getBounds().width * 1.5f, _text->getBounds().height * 2.f});
	_normalSprite->setSize(this->getSize());
	_hoveredSprite->setSize(this->getSize());
	_clickedSprite->setSize(this->getSize());
	textPos = Vector2d(this->getPos().x + this->_size.x / 2, this->getPos().y + this->_size.y / 2);
	_text->setPosition(textPos);
	textBounds = _text->getBounds();
	_text->setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
}

void OtterEngine::Button::setText(std::string str)
{
	Vector2d textPos;
	sf::FloatRect textBounds;

	_text->setString(str);
	this->setSize({_text->getBounds().width * 1.5f, _text->getBounds().height * 2.f});
	_normalSprite->setSize(this->getSize());
	_hoveredSprite->setSize(this->getSize());
	_clickedSprite->setSize(this->getSize());
	textPos = Vector2d(this->getPos().x + this->_size.x / 2, this->getPos().y + this->_size.y / 2);
	_text->setPosition(textPos);
	textBounds = _text->getBounds();
	_text->setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
}

void OtterEngine::Button::setFont(sf::Font &font)
{
	Vector2d textPos;
	sf::FloatRect textBounds;

	this->_text->setFont(font);
	this->setSize({_text->getBounds().width * 1.5f, _text->getBounds().height * 2.f});
	_normalSprite->setSize(this->getSize());
	_hoveredSprite->setSize(this->getSize());
	_clickedSprite->setSize(this->getSize());
	textPos = Vector2d(this->getPos().x + this->_size.x / 2, this->getPos().y + this->_size.y / 2);
	_text->setPosition(textPos);
	textBounds = _text->getBounds();
	_text->setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
}

Vector2d OtterEngine::Button::getPosition()
{
	return this->getPos();
}

Vector2d OtterEngine::Button::getDimensions()
{
	return this->getSize();
}

OtterEngine::Button::State OtterEngine::Button::getState()
{
	return this->_state;
}

void OtterEngine::Button::update(sf::Event &event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*WindowManager::getInstance()->getWindow());
	double minPosX = this->getPos().x - this->_size.x / 2;
	double maxPosX = this->getPos().x + this->_size.x / 2;
	double minPosY = this->getPos().y - this->_size.y / 2;
	double maxPosY = this->getPos().y + this->_size.y / 2;

	bool mouseInButton = mousePosition.x >= minPosX && mousePosition.x <= maxPosX
		&& mousePosition.y >= minPosY && mousePosition.y <= maxPosY;

	if (event.type == sf::Event::MouseMoved) {
		if (mouseInButton) {
			if (_state == NORMAL) {
				SpritesManager::getInstance()->removeSprite(_normalSprite);
				SpritesManager::getInstance()->removeSprite(_clickedSprite);
				SpritesManager::getInstance()->addSprite(this->_layer, _hoveredSprite);
				_state = HOVERED;
			}
		}
		else if (_state != NORMAL) {
			SpritesManager::getInstance()->removeSprite(_hoveredSprite);
			SpritesManager::getInstance()->removeSprite(_clickedSprite);
			SpritesManager::getInstance()->addSprite(this->_layer, _normalSprite);
			_state = NORMAL;
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (mouseInButton && _state != CLICKED) {
				_called = false;
				SpritesManager::getInstance()->removeSprite(_hoveredSprite);
				SpritesManager::getInstance()->removeSprite(_normalSprite);
				SpritesManager::getInstance()->addSprite(this->_layer, _clickedSprite);
				_state = CLICKED;
			}
			else if (!mouseInButton && _state != NORMAL){
				SpritesManager::getInstance()->removeSprite(_hoveredSprite);
				SpritesManager::getInstance()->removeSprite(_clickedSprite);
				SpritesManager::getInstance()->addSprite(this->_layer, _normalSprite);
				_state = NORMAL;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (mouseInButton && _state != HOVERED) {
				if (!_called) {
					_called = true;
					_callback(_data);
				}
				SpritesManager::getInstance()->removeSprite(_normalSprite);
				SpritesManager::getInstance()->removeSprite(_clickedSprite);
				SpritesManager::getInstance()->addSprite(this->_layer, _hoveredSprite);
				_state = HOVERED;
			}
			else if (!mouseInButton && _state != NORMAL) {
				SpritesManager::getInstance()->removeSprite(_hoveredSprite);
				SpritesManager::getInstance()->removeSprite(_clickedSprite);
				SpritesManager::getInstance()->addSprite(this->_layer, _normalSprite);
				_state = NORMAL;
			}
		}
	}
}

void OtterEngine::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	(void)target;
	(void)states;
}

void OtterEngine::Button::setCallback(Button::Callback callback)
{
	_callback = std::move(callback);
}
