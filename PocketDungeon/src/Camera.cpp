//
// Created by flav on 1/10/19.
//

#include <OtterEngine/WindowManager.hpp>
#include <iostream>
#include "Camera.h"

Camera::Camera(OtterEngine::View *view, Player *player) : _view(view), _player(player) {
	_name += "Camera::";
	addEvent<Camera>(_events, OtterEngine::Event<Camera>("update", &Camera::update, &Camera::always));
}

Camera::~Camera()
{

}

bool Camera::always(OtterEngine::Engine *) {
	return true;
}

int Camera::update(OtterEngine::Engine *) {
	_view->setPosition(sf::Vector2f(_player->getPos().x, _player->getPos().y));
	WindowManager::getInstance()->getWindow()->setView(*_view->getView());
}

void Camera::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
