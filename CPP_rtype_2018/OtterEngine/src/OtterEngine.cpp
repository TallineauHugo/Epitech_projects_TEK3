#include <iostream>
#include "OtterEngine.hpp"
#include "Object.hpp"
#include "TimeManager.hpp"

OtterEngine::Engine::Engine() : _graph(true)
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

void OtterEngine::Engine::removeObject(int index)
{
	_removeList.push_back(index);
}

void OtterEngine::Engine::removeObjectById(std::size_t id)
{
	std::vector<Object*>::iterator it = _objs.begin();

	while (it != _objs.end()) {
		if ((*it)->getId() == id) {
			_removeList.push_back(this->getIndex(*it));
			break;
		}
		it++;
	}
}

void OtterEngine::Engine::update()
{
	TimeManager::getInstance()->update();
	if (!_graph) {
		applyVelo();
		calculateColisions();
		checkEvents();
	}
	removeObjects();
	if (_graph)
		SpritesManager::getInstance()->refresh();
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
	for (std::size_t i = 0; i < _objs.size() - 1; i++) {
		for (std::size_t i2 = i + 1; i2 < _objs.size(); i2++)
			if (_objs[i]->getHitbox().doCollide(_objs[i2]->getHitbox()))
				_cols.insert(std::pair<int,int>(i,i2));
	}
}

void OtterEngine::Engine::checkEvents()
{
	for (std::size_t i = 0; i < _objs.size(); i++)
		_objs[i]->updateEvents(this);
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
