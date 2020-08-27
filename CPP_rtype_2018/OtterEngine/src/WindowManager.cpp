//
// EPITECH PROJECT, 2018
// jam
// File description:
// windowmanager
//

#include "WindowManager.hpp"

WindowManager::WindowManager()
{
	_window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes().front(),
				       "Otter Engine", sf::Style::Fullscreen);
}

WindowManager::~WindowManager()
{}

void WindowManager::draw(sf::Drawable &drawable)
{
	_window->draw(drawable);
}

bool WindowManager::isOpen() const
{
	return _window->isOpen();
}

bool WindowManager::hasFocus() const
{
	return _window->hasFocus();
}

bool WindowManager::pollEvent(sf::Event &event)
{
	return _window->pollEvent(event);
}

void WindowManager::close()
{
	_window->close();
}

void WindowManager::clear()
{
	_window->clear();
}

void WindowManager::display()
{
	_window->display();
}

sf::Vector2u WindowManager::getSize() const
{
	return _window->getSize();
}

sf::RenderWindow *WindowManager::getWindow() const
{
	return this->_window;
}

void WindowManager::setView(sf::Vector2f pos, sf::Vector2f size) {
	_view = OtterEngine::View::getInstance(pos, size);
	_window->setView(*_view->getView());
}

void WindowManager::setDefaultView() {
	_window->setView(_window->getDefaultView());
}

OtterEngine::View *WindowManager::getView() {
	return _view;
}
