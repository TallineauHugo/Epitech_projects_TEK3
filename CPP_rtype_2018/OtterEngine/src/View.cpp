#include "View.hpp"

OtterEngine::View::View(sf::Vector2f pos, sf::Vector2f size) : _pos(pos), _size(size)
{
        _view = new sf::View(_pos, _size);
}

OtterEngine::View::~View()
{}

void OtterEngine::View::setPosition(const sf::Vector2f pos)
{
        _pos = pos;
        getView()->setCenter(pos);
}

sf::Vector2f OtterEngine::View::getPosition(void) const {
        return _pos;
}
void OtterEngine::View::setSize(const sf::Vector2f size)
{
        _size = size;
        getView()->setSize(size);
}

sf::Vector2f OtterEngine::View::getSize(void) const {
        return _size;
}

sf::View *OtterEngine::View::getView(void) const {
        return _view;
}
