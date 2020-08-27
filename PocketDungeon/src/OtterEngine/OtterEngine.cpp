#include <iostream>
#include "OtterEngine.hpp"
#include "InputManager.hpp"

#include "Object.hpp"
#include "TimeManager.hpp"
#include "IA.hpp"
#include <math.h>

#define PI 3.14159265

OtterEngine::Engine::Engine() : _graph(true), _pause(false), _quit(0)
{
}

OtterEngine::Engine::~Engine()
{
}

void OtterEngine::Engine::setGraphicalMode(bool g)
{
	_graph = g;
}

std::vector<OtterEngine::Object *>& OtterEngine::Engine::getObjs()
{
	return _objs;
}

std::vector<IA *>& OtterEngine::Engine::getListIA()
{
	return _ListIA;
}

OtterEngine::Object *OtterEngine::Engine::getObjectById(std::size_t id) const
{
	std::vector<OtterEngine::Object *>::const_iterator it = _objs.begin();

	while (it != _objs.end()) {
		if ((*it)->getId() == id)
			return *it;
		it++;
	}
	return nullptr;
}

std::map<int, int>& OtterEngine::Engine::getCols()
{
	return _cols;
}

void OtterEngine::Engine::addObject(OtterEngine::Object *obj)
{
	_objs.push_back(obj);
}

void OtterEngine::Engine::addIA(IA *ia)
{
	_ListIA.push_back(ia);
}

void OtterEngine::Engine::removeObject(int index)
{
	_removeList.push_back(index);
}

void OtterEngine::Engine::removeObjectById(std::size_t id)
{
	std::vector<Object*>::iterator it = _objs.begin();

	while (it != _objs.end()) {
		if (this->getIndex(*it) == id) {
			_removeList.push_back(this->getIndex(*it));
			break;
		}
		it++;
	}
}

int OtterEngine::Engine::update()
{
	static float timer = 0.0f;
	if (timer == 0.0f) {
		timer = TimeManager::getInstance()->getTotalTime();
	}

	TimeManager::getInstance()->update();
	if (!_pause) {
		_sm.refresh();
		applyVelo();
		calculateColisions();
		if ((TimeManager::getInstance()->getTotalTime() - timer) >= 0.01f) {
			updateIA(true);
			timer = TimeManager::getInstance()->getTotalTime();
		}
		else
			updateIA(false);
		checkEvents();
	}
	removeObjects();
	SpritesManager::getInstance()->refresh();
	return _quit;
	// else if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::Q))
	// 	pause();
}

void OtterEngine::Engine::pause()
{
	std::cout << "On fait pause aksip" << std::endl;
	if (!_pause) {
		_pause = true;
		_sm.pauseSounds();
	}
	else
	{
		_pause = false;
		_sm.resumeSounds();
	}
}

void OtterEngine::Engine::restart() {
	_quit = 1;
}

void OtterEngine::Engine::normalize()
{
	_quit = 0;
}

void OtterEngine::Engine::updateIA(bool verif)
{
	if (verif) {
		for (int i = 0; i < _ListIA.size(); i++) {
			if (_ListIA[i]->GetCurrentPokemon() != NULL && _ListIA[i]->GetCurrentPokemon()->getInertness() == false){
				if ((int)(_ListIA[i]->getPlayer()->getPos().x) < (int)(_ListIA[i]->GetCurrentPokemon()->getPos().x)) {
					_ListIA[i]->LeftReaction(this);
					_ListIA[i]->GetCurrentPokemon()->getVelocity().x = -250;
				}
				else {
					_ListIA[i]->RightReaction(this);
					_ListIA[i]->GetCurrentPokemon()->getVelocity().x = 250;
				}
				if ((int)(_ListIA[i]->getPlayer()->getPos().y) < (int)(_ListIA[i]->GetCurrentPokemon()->getPos().y)) {
					_ListIA[i]->UpReaction(this);
					_ListIA[i]->GetCurrentPokemon()->getVelocity().y = -250;
				}
				else if ((int)(_ListIA[i]->getPlayer()->getPos().y) > (int)(_ListIA[i]->GetCurrentPokemon()->getPos().y)) {
					_ListIA[i]->DownReaction(this);
					_ListIA[i]->GetCurrentPokemon()->getVelocity().y = 250;
				}
				int delta_x = (int)(_ListIA[i]->getPlayer()->getPos().x) - (int)(_ListIA[i]->GetCurrentPokemon()->getPos().x);
				int delta_y = (int)(_ListIA[i]->getPlayer()->getPos().y) - (int)(_ListIA[i]->GetCurrentPokemon()->getPos().y);
				float dist = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

				float radian = acos(delta_x / sqrt(pow(delta_x, 2) + pow(delta_y, 2)));
				float radian2 = asin(delta_y / sqrt(pow(delta_x, 2) + pow(delta_y, 2)));

				if (_ListIA[i]->getPlayer()->getPos().x < _ListIA[i]->GetCurrentPokemon()->getPos().x && _ListIA[i]->getPlayer()->getPos().y > _ListIA[i]->GetCurrentPokemon()->getPos().y)
					radian = radian;
				else if (radian != radian2)
					radian *=-1;
				radian = (radian * 180.0 / PI) - 90;
				std::cout << "radian: " << radian << std::endl;
				_ListIA[i]->GetCurrentPokemon()->setAngleShot(radian);
				for (int j = 0; j < 4; j++)
				{
					if (_ListIA[i]->GetCurrentPokemon()->getAtkManager().getAtkRange(j) >= dist && !_ListIA[i]->GetCurrentPokemon()->attack(j, this))
						break;
				}
			}
		}
	}
	// else {
	// 	for (int i = 0; i < _ListIA.size(); i++) {
	// 		_ListIA[i]->NoLeftReaction(this);
	// 		_ListIA[i]->NoRightReaction(this);
	// 		_ListIA[i]->NoDownReaction(this);
	// 		_ListIA[i]->NoUpReaction(this);
	// 	}
	// }
}

int OtterEngine::Engine::getIndex(Object *obj)
{
	for (std::size_t i = 0; i < _objs.size(); i++)	{
		if (_objs[i] == obj)
			return i;
	}
	return -1;
}

std::list<std::size_t> OtterEngine::Engine::getRemovedList()
{
	std::list<std::size_t> tmp = _removedList;

	_removedList.clear();
	return tmp;
}

void OtterEngine::Engine::calculateColisions()
{
	if (_objs.size() == 0)
		return;
	for (std::size_t i = 0; i < _objs.size() - 1; i++) {
		for (std::size_t i2 = i + 1; i2 < _objs.size(); i2++)
			if (_objs[i]->getHitbox().doCollide(_objs[i2]->getHitbox()))
				_cols.insert(std::pair<int,int>(i,i2));
	}
}

void OtterEngine::Engine::clearEngine()
{
	if (_pause)
		pause();
	_mm.stop();
	OtterEngine::SpritesManager::getInstance()->clear();
	removeIAs();
	removeObjects();
	while (_objs.size() != 0)
		_objs.erase(_objs.begin());
}

void OtterEngine::Engine::checkEvents()
{
	for (std::size_t i = 0; i < _objs.size(); i++) {
			_objs[i]->updateEvents(this);
	}
}


void OtterEngine::Engine::removeIAs()
{
	while (_ListIA.size() != 0)
		_ListIA.erase(_ListIA.begin());
}

void OtterEngine::Engine::removeObjects()
{
	int i = 0;

	_cols.clear();
	_removeList.unique();
	_removeList.sort();
    while (_removeList.size() > 0) {
		_removedList.push_back(_objs[_removeList.front() - i]->getId());
		_objs.erase(_objs.begin() + _removeList.front() - i);
		_removeList.pop_front();
		i++;
	}
}

void OtterEngine::Engine::applyVelo()
{
	for (std::size_t i = 0; i < _objs.size(); i++) {
		_objs[i]->applyVelocity();
	}
}

bool OtterEngine::Engine::getPause() {
	return _pause;
}
