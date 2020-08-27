#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "WindowManager.hpp"
#include "Slider.hpp"

OtterEngine::Slider::Slider(Vector2d pos, Vector2d size, int &data, int min, int max):_data(data), _min(min), _max(max)
{
	this->setPos(this->getPos());
	_size = size;
	_slider.setPosition((float)this->getPos().x, (float)this->getPos().y + (float)(_size.y / 4) * 3);
	_slider.setSize({(float)_size.x, (float)_size.y / 4});
	_slider.setFillColor(sf::Color::White);
	_leftHandle.setPosition({(float)this->getPos().x, (float)(this->getPos().y + _size.y -_size.y / 1.5f)});
	_leftHandle.setSize({5, (float)_size.y / 1.5f});
	_leftHandle.setFillColor(sf::Color::White);
	_rightHandle.setPosition({(float)(this->getPos().x + _size.x - 5), (float)(this->getPos().y + _size.y - _size.y / 1.5f)});
	_rightHandle.setSize({5, (float)_size.y / 1.5f});
	_rightHandle.setFillColor(sf::Color::White);
	_cursor.setSize({15, (float)_size.y * 2});
	_cursor.setOrigin({15 / 2, (float)_size. y / 2});
	_cursor.setPosition({(float)(this->getPos().x + ((float)(data - min) / (max - min) * _size.x)), (float)(this->getPos().y + _size.y - _size.y / 1.5f)});
	_cursor.setFillColor(sf::Color::White);
	_dragging = false;
	(void)pos;
}

OtterEngine::Slider::~Slider()
{
}

void OtterEngine::Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_slider, states);
	target.draw(_leftHandle, states);
	target.draw(_rightHandle, states);
	target.draw(_cursor, states);
}

void OtterEngine::Slider::update(sf::Event &event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*WindowManager::getInstance()->getWindow());
	bool mouseInCursor = mousePosition.x >= _cursor.getPosition().x - _cursor.getGlobalBounds().width / 2
		&& mousePosition.x <= _cursor.getPosition().x + _cursor.getGlobalBounds().width / 2
		&& mousePosition.y >= _cursor.getPosition().y - _cursor.getGlobalBounds().height / 2
		&& mousePosition.y <= _cursor.getPosition().y + _cursor.getGlobalBounds().height;

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
			if (mousePosition.x < _slider.getPosition().x)
				mousePosition.x = (int)_slider.getPosition().x;
			if (mousePosition.x > _slider.getPosition().x + _slider.getSize().x)
				mousePosition.x = (int)(_slider.getPosition().x + _slider.getSize().x);
			_cursor.setPosition({(float)mousePosition.x, _cursor.getPosition().y});
			_data = _min + (((_max - _min) * (int)getFactor()) / 100);
		}
	}
}

float OtterEngine::Slider::getFactor()
{
	return (_cursor.getPosition().x - _slider.getPosition().x) / _slider.getSize().x * 100;
}