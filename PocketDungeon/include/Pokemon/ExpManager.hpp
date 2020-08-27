//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// exp manager
//

#pragma once

#include <string>
#include <cstddef>

class Pokemon;

class ExpManager
{
public:
	ExpManager();
	~ExpManager();
public:
	void setExpOnDeath(std::size_t value);
	
	std::size_t getLvl() const;
	std::size_t getNextLvlExp() const;
	std::size_t getTotalExp() const;
	std::size_t getExpOnDeath() const;

	std::size_t& getRefCurrentExp();
	std::size_t& getRefNextLvlExp();

	void gainExp(std::size_t value, Pokemon *pkmn);
private:
	void processNextLvlExp();
private:
	std::size_t _lvl;
	std::size_t _totalExp;
	std::size_t _nextLvlExp;
	std::size_t _expOnDeath;
	std::size_t _lastLvlUp;
	std::size_t _currentPercent;
	std::size_t _maxPercent;
};
