#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "WindowManager.hpp"
#include "SpriteSlider.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"

OtterEngine::SpriteSlider::SpriteSlider(std::string filename, Vector2d pos, int layer, Vector2d size, int &data, int min, int max):_data(data), _min(min), _max(max)
{
	SpritesManager *spritesManager = SpritesManager::getInstance();

	this->setPos(pos);
	this->_size = size;

	_leftHandle = new FixedSprite();
	_rightHandle = new FixedSprite();
	_slider = new FixedSprite();
	_cursor = new FixedSprite();

	_leftHandle->loadSpriteFromFile(filename, {0, 0, 10, 25});
	_rightHandle->loadSpriteFromFile(filename, {10, 0, 10, 25});
	_cursor->loadSpriteFromFile(filename, {20, 0, 10, 25});
	_slider->loadSpriteFromFile(filename, {0, 25, 100, 10});

	_leftHandle->setSize({(_size.y / 25.f * 10), _size.y});
	_leftHandle->setPosition({this->getPos().x, this->getPos().y});

	_rightHandle->setSize({(_size.y / 25.f * 10), _size.y});
	_rightHandle->setPosition({this->getPos().x + _size.x - (int)(_size.y / 25.f * 10) * 2, this->getPos().y});

	_slider->setSize({size.x - ((_size.y / 25.f * 10) * 3), (_size.y / 25.f * 10)});
	_slider->setPosition({this->getPos().x + (int)(_size.y / 25.f * 10), this->getPos().y + size.y - (int)(_size.y / 25.f * 10)});

	_cursor->setPosition({this->getPos().x + (int)((float)(data - min) / (max - min) * _size.x) - ((_size.y / 25.f * 10) * 2) / 2, pos.y - (int)(_size.y / 25.f * 25) / 2 + (int)(_size.y / 25.f * 10) / 2});
	_cursor->setSize({(_size.y / 25.f * 10) * 2, _size.y * 2});

	_dragging = false;

	spritesManager->addSprite(layer, _slider);
	spritesManager->addSprite(layer, _leftHandle);
	spritesManager->addSprite(layer, _rightHandle);
	spritesManager->addSprite(layer, _cursor);
}

OtterEngine::SpriteSlider::~SpriteSlider()
{
}

void OtterEngine::SpriteSlider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	(void)target;
	(void)states;
}

void OtterEngine::SpriteSlider::update(sf::Event &event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*WindowManager::getInstance()->getWindow());
	bool mouseInCursor;

	this->updateSprites();
	mouseInCursor = mousePosition.x >= _cursor->getPosition().x
		&& mousePosition.x <= _cursor->getPosition().x + _cursor->getSize().x
		&& mousePosition.y >= _cursor->getPosition().y
		&& mousePosition.y <= _cursor->getPosition().y + _cursor->getSize().y;
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && mouseInCursor)
			_dragging = true;
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left)
			_dragging = false;
	}

	if (event.type == sf::Event::MouseMoved) {
		if (_dragging) {
			if (mousePosition.x < _slider->getPosition().x)
				mousePosition.x = _slider->getPosition().x;
			if (mousePosition.x > _rightHandle->getPosition().x - _cursor->getSize().x)
				mousePosition.x = _rightHandle->getPosition().x - _cursor->getSize().x;
			_cursor->setPosition({(double)mousePosition.x, this->getPos().y - (int)(_size.y / 25.f * 25) / 2 + (int)(_size.y / 25.f * 10) / 2});
			_data = _min + (((_max - _min) * (int)getFactor()) / 100);
		}
	}
}

float OtterEngine::SpriteSlider::getFactor()
{
	return ((float)(_cursor->getPosition().x - _slider->getPosition().x)) / (_slider->getSize().x - _cursor->getSize().x) * 100;
}

void OtterEngine::SpriteSlider::updateSprites()
{
	double cursorPosX = this->getPos().x + (int)((float)(_data - _min) / (_max - _min) * _size.x) - ((_size.y / 25.f * 10) * 2) / 2;

	if (cursorPosX < _slider->getPosition().x)
		cursorPosX = _slider->getPosition().x;
	if (cursorPosX > _rightHandle->getPosition().x - _cursor->getSize().x)
		cursorPosX = _rightHandle->getPosition().x - _cursor->getSize().x;
	_leftHandle->setPosition({this->getPos().x, this->getPos().y});
	_rightHandle->setPosition({this->getPos().x + _size.x - (int)(_size.y / 25.f * 10) * 2, this->getPos().y});
	_slider->setPosition({this->getPos().x + (int)(_size.y / 25.f * 10), this->getPos().y + _size.y - (int)(_size.y / 25.f * 10)});
	_cursor->setPosition({cursorPosX, this->getPos().y - (int)(_size.y / 25.f * 25) / 2 + (int)(_size.y / 25.f * 10) / 2});
}
