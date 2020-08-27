#include "Menu.hpp"
#include "WindowManager.hpp"

#include <iostream>
OtterEngine::Menu::Menu(Vector2d pos, Vector2d size, Align align) : _pos(pos), _size(size), _align(align)
{
}

OtterEngine::Menu::~Menu()
{
}

void OtterEngine::Menu::addElement(OtterEngine::MenuElement *element)
{
	Vector2d elemPos;

	if (!this->isElementInMenu(element)) {
		if (_align == LEFT)
			elemPos.x = this->_pos.x + element->getOffset().x;
		else if (_align == RIGHT)
			elemPos.x = this->_pos.x + this->_size.x - element->getSize().x + element->getOffset().x;
		else if (_align == CENTERED)
			elemPos.x = this->_pos.x + this->_size.x / 2 - element->getSize().x / 2 + element->getOffset().x;
		if (!this->_elements.empty())
			elemPos.y = this->_elements[this->_elements.size() - 1]->getPos().y + this->_elements[this->_elements.size() - 1]->getSize().y + 50 + element->getOffset().y - this->_elements[this->_elements.size() - 1]->getOffset().y;
		else
			elemPos.y = this->_pos.y + element->getOffset().y;
		element->setPos(elemPos);
		this->_elements[this->_elements.size()] = element;
	}
}

bool OtterEngine::Menu::isElementInMenu(OtterEngine::MenuElement *element)
{
	std::map<int, MenuElement*>::iterator it = this->_elements.begin();

	while (it != this->_elements.end()) {
		if (it->second == element) {
			return true;
		}
		it++;
	}
	return false;
}

void OtterEngine::Menu::update(sf::Event &event)
{
	std::map<int, MenuElement*>::iterator it = this->_elements.begin();

	while (it != this->_elements.end()) {
		it->second->update(event);
		it++;
	}
}
