//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// exp manager
//

#include <cmath>
#include "ExpManager.hpp"
#include "Pokemon.hpp"

ExpManager::ExpManager() : _lvl(1), _totalExp(0), _nextLvlExp(1), _expOnDeath(1), _lastLvlUp(0), _currentPercent(0), _maxPercent(1)
{
}

ExpManager::~ExpManager()
{}

void ExpManager::setExpOnDeath(std::size_t value)
{
	_expOnDeath = value;
}

std::size_t ExpManager::getLvl() const
{
	return _lvl;
}

std::size_t ExpManager::getNextLvlExp() const
{
	return _nextLvlExp;
}

std::size_t ExpManager::getTotalExp() const
{
	return _totalExp;
}

std::size_t ExpManager::getExpOnDeath() const
{
	return _expOnDeath;
}
#include <iostream>
void ExpManager::gainExp(std::size_t value, Pokemon *pkmn)
{
	std::cout << "exp: " << _totalExp << " -> " << _totalExp + value << " / " << _nextLvlExp << std::endl;	
	_totalExp += value;
	
	while (_totalExp >= _nextLvlExp) {
		std::cout << "[ExpManager]: totalExp=" << _totalExp << " | next=" << _nextLvlExp << std::endl;
		_lvl++;
		pkmn->updateMoves();
		std::cout << "Level up ! now lvl " << _lvl << std::endl;
		processNextLvlExp();
	}
	_maxPercent = ((_nextLvlExp - _lastLvlUp) < 0) ? 0 : _nextLvlExp - _lastLvlUp;
	_currentPercent = ((_totalExp - _lastLvlUp) < 0) ? 0 : _totalExp - _lastLvlUp;
	std::cout << "%: " << ((float)(_totalExp - _lastLvlUp) / (float)(_nextLvlExp - _lastLvlUp)) * 100 << std::endl;
}

void ExpManager::processNextLvlExp()
{
	_lastLvlUp = pow((float)(_lvl - 1.0), 3.0);
	_nextLvlExp = pow((float)_lvl, 3.0);
}

std::size_t &ExpManager::getRefCurrentExp() // total - last
{
	return _currentPercent;
}

std::size_t &ExpManager::getRefNextLvlExp()
{
	return _maxPercent;
}