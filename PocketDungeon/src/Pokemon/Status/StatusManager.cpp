//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// status manager
//

#include "StatsManager.hpp"
#include "StatusManager.hpp"
#include "Burn.hpp"
#include "Freeze.hpp"
#include "Paralysis.hpp"
#include "Poison.hpp"
#include "BadlyPoison.hpp"
#include "Sleep.hpp"
#include "StatBuff.hpp"
#include "StatDebuff.hpp"

bool Status::StatusManager::haveStatus(Status status) const
{
	if (!_currentStatus)
		return false;
	return _currentStatus->isStatus(status);
}

bool Status::StatusManager::applyStatusFor(Status status, float seconds)
{
	if (_currentStatus)
		return false;
	switch (status) {
		case Status::BURN:
			_currentStatus = new Burn(status, seconds, _statsManager);
			break;
		case Status::FREEZE:
		_currentStatus = new Freeze(status, seconds, _statsManager);
			break;
		case Status::PARALYSIS:
			_currentStatus = new Paralysis(status, seconds, _statsManager);
			break;
		case Status::POISON:
			_currentStatus = new Poison(status, seconds, _statsManager);
			break;
		case Status::BADLY_POISON:
			_currentStatus = new BadlyPoison(status, seconds, _statsManager);
			break;
		case Status::SLEEP:
			_currentStatus = new Sleep(status, seconds, _statsManager);
			break;
		case Status::ATKBUFF:
			_secondaryStatus.push_back(new StatBuff(ATK, seconds, _statsManager));
			break;
		case Status::ATKDEBUFF:
			_secondaryStatus.push_back(new StatDebuff(ATK, seconds, _statsManager));
			break;
		default:
			return false;
	}
	return true;
}

bool Status::StatusManager::canMove() const
{
	if (!_currentStatus)
		return true;
	return _currentStatus->canMove();
}

void Status::StatusManager::update(float deltaTime)
{
	if (_currentStatus) {
		if (!_currentStatus->update(deltaTime)) {
			delete _currentStatus;
			_currentStatus = nullptr;
		}
	}
	std::list<IStatus *>::iterator i = _secondaryStatus.begin();
	while (i != _secondaryStatus.end()) {
		if (!(*i)->update(deltaTime)) {
			i = _secondaryStatus.erase(i);
		}
		else
			i++;
	}
}

void Status::StatusManager::setStatsManager(StatsManager *manager)
{
	_statsManager = manager;
}

Status::StatusManager::StatusManager()
: _currentStatus(nullptr), _statsManager(nullptr)
{}

Status::StatusManager::~StatusManager()
{
	if (_currentStatus)
		delete _currentStatus;
}