#include "ScrollingCamera.hpp"
#include "WindowManager.hpp"
#include "View.hpp"
#include <iostream>

ScrollingCamera::ScrollingCamera(OtterEngine::View *view) : _view(view)
{
	_velocity.x = 100;
	_hitbox.setPos(Vector2d(_view->getPosition().x, _view->getPosition().y));
	_name += "ScrollingCamera::";
	addEvent<ScrollingCamera>(_events, OtterEngine::Event<ScrollingCamera>("update", &ScrollingCamera::update, &ScrollingCamera::always));
}

ScrollingCamera::~ScrollingCamera()
{
	
}

bool ScrollingCamera::always(OtterEngine::Engine *)
{
	return true;
}

int ScrollingCamera::update(OtterEngine::Engine *)
{
	_view->setPosition(sf::Vector2f(getPos().x, getPos().y));
	WindowManager::getInstance()->getWindow()->setView(*_view->getView());
}

void ScrollingCamera::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
