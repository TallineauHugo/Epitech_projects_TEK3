//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// stats manager
//

#include <iostream>

#include "StatsManager.hpp"
#include "TypeTable.hpp"
#include "Pokemon.hpp"
#include "Attack.hpp"
#include "Parser.hpp"

StatsManager::StatsManager() : _pEvolve(0, ""), _totalEv(0), _hp(1), _maxHp(1), _dmgMultiplier(1), _host(nullptr)
{
	_ev[HP] = 0;
	_ev[ATK] = 0;
	_ev[DEF] = 0;
	_ev[ATKSPE] = 0;
	_ev[DEFSPE] = 0;
	_ev[SPEED] = 0;

	_mBuffLevel[HP] = 0;
	_mBuffLevel[ATK] = 0;
	_mBuffLevel[DEF] = 0;
	_mBuffLevel[ATKSPE] = 0;
	_mBuffLevel[DEFSPE] = 0;
	_mBuffLevel[SPEED] = 0;

	_mBuffMultiplier[-6] = 1 / 4;
	_mBuffMultiplier[-5] = 2 / 7;
	_mBuffMultiplier[-4] = 1 / 3;
	_mBuffMultiplier[-3] = 2 / 5;
	_mBuffMultiplier[-2] = 1 / 2;
	_mBuffMultiplier[-1] = 2 / 3;
	_mBuffMultiplier[0] = 1;
	_mBuffMultiplier[1] = 3 / 2;
	_mBuffMultiplier[2] = 2;
	_mBuffMultiplier[3] = 5 / 2;
	_mBuffMultiplier[4] = 3;
	_mBuffMultiplier[5] = 7 / 2;
	_mBuffMultiplier[6] = 4;

	_status.setStatsManager(this);

	_pEvolve.first = 101;
	_pEvolve.second = "";

	_mStat[HP] = 0;
	_mStat[ATK] = 0;
	_mStat[DEF] = 0;
	_mStat[ATKSPE] = 0;
	_mStat[DEFSPE] = 0;
	_mStat[SPEED] = 0;
}

StatsManager::~StatsManager()
{
	_status.setStatsManager(nullptr);
}

bool StatsManager::haveStatus(Status::Status status) const
{
	return _status.haveStatus(status);
}

float StatsManager::getBuffMultiplier(std::string stat) const
{
	float ret = 1;

	if (_mBuffLevel.find(stat) == _mBuffLevel.end())
		return ret;
	ret = _mBuffMultiplier.at(_mBuffLevel.at(stat));
	if (ret > 6)
		ret = 6;
	else if (ret < -6)
		ret = -6;
	return ret;
}

void StatsManager::applyBuff(std::string stat, int lvlToAdd)
{
	if (_mBuffLevel.find(stat) == _mBuffLevel.end())
		return;
	_mBuffLevel[stat] += lvlToAdd;
}

bool StatsManager::applyStatusFor(Status::Status status, float seconds)
{
	return _status.applyStatusFor(status, seconds);
}

bool StatsManager::canMove() const
{
	return _status.canMove();
}

void StatsManager::update(float deltaTime)
{
	_status.update(deltaTime);
}

void StatsManager::gainEv(std::string type, std::size_t amount)
{
	if (_ev[type] + amount > 252)
		amount = 252 - _ev[type];
	if (_totalEv + amount > 510)
		amount = 510 - _totalEv;
	_ev[type] += amount;
	_totalEv += amount;
}

bool StatsManager::takeDamage(Attack atk)
{
	std::size_t amount;
	float modifiers;
	float targets = 1.0;
	float weather = 1.0;
	float critical = 1.0;
	float random = 1.0;
	float stab = 1.0;
	float type = 1.0;
	float burn = 1.0;
	float other = 1.0;

	Pokemon *host = atk.getHost();

	//base
	amount = ((((2 * host->getLvl()) / 5) + 2) * atk.getPower());
	if (atk.getType() == DamageType::PHYSICAL) {
		amount = amount * host->getAtk() / this->getStat("def");
	}
	else if (atk.getType() == DamageType::SPECIAL)
		amount = amount * host->getAtkSpe() / this->getStat("defSpe");
	amount = amount / 50 + 2;

	//modificateurs
	//	nb Targets
	//	weather / terrain
	//	crit

	if (atk.getCritRate() > rand() % 101) {
		std::cout << "Critical strike !" << std::endl;
		critical = 2;
	}
	//	random
	//random = (float)((rand() % 39) + 217) / 255;
	//	STAB
	//	type
	type = TypeTable::getInstance()->getMultiplier(this->getType(), atk.getElement());
	std::cout << "type multiplier: " << type << std::endl;
	//	other (item, special attacks, ...) cf site favoris avec liste spells concernés
	other = _dmgMultiplier;

	modifiers = targets * weather * critical * random * stab * type * burn * other;
	amount = (float)amount * modifiers;


	std::cout << "Amount of dmg: " << amount << std::endl;

	return this->loseLife(amount);
}

bool StatsManager::loseLife(std::size_t amount)
{
	if (amount < 1)
		amount = 1;

	if (amount > _hp) {
		_hp = 0;
		//set le statut à KO
	}
	else
		_hp -= amount;

	return _hp > 0;
}

void StatsManager::lvlUp()
{
	int nb = _exp.getNextLvlExp() - _exp.getTotalExp();

	if (nb > 0)
		_exp.gainExp(nb, _host);
}

void StatsManager::gainExp(std::size_t amount)
{
	std::size_t old = _exp.getLvl();
	_exp.gainExp(amount, _host);
	if (old != _exp.getLvl() && _pEvolve.first <= _exp.getLvl())
		_host->evolve();
}

void StatsManager::heal(std::size_t amount)
{
	std::size_t maxHp = this->getMaxHp();

	_hp += amount;
	if (_hp > maxHp)
		_hp = maxHp;
}

void StatsManager::updateStats()
{
	std::size_t lvl = _exp.getLvl();
	float percentHp;

	percentHp = (_mStat[HP] == 0) ? 100 : _hp * 100 / _mStat[HP];

	_mStat[HP] = ((((2 * _mBaseStat[HP] + _iv[HP]  + (_ev[HP] / 4)) * lvl) / 100) + lvl + 10);
	_mStat[ATK] = (((2 * _mBaseStat[ATK] + _iv[ATK] + (_ev[ATK] / 4)) * lvl) / 100 + 5);
	_mStat[DEF] = (((2 * _mBaseStat[DEF] + _iv[DEF] + (_ev[DEF] / 4)) * lvl) / 100 + 5);
	_mStat[ATKSPE] = (((2 * _mBaseStat[ATKSPE] + _iv[ATKSPE] + (_ev[ATKSPE] / 4)) * lvl) / 100 + 5);
	_mStat[DEFSPE] = (((2 * _mBaseStat[DEFSPE] + _iv[DEFSPE] + (_ev[DEFSPE] / 4)) * lvl) / 100 + 5);
	_mStat[SPEED] = (((2 * _mBaseStat[SPEED] + _iv[SPEED] + (_ev[SPEED] / 4)) * lvl) / 100 + 5);

	_hp = _mStat[HP];// * (percentHp / 100);
	_maxHp = _mStat[HP];
	std::cout << "max hp: " << this->getStat(HP) << std::endl;
}

//getter and setter

void StatsManager::setDmgMultiplier(float value)
{
	_dmgMultiplier = value;
}

void StatsManager::setBaseStat(std::pair<std::string, std::string> stat)
{
	_mBaseStat[stat.first] = std::stoi(stat.second);
	_mStat[stat.first] = 0;
}

void StatsManager::setIv(std::string stat, std::size_t value)
{
	_iv[stat] = value;
}

void StatsManager::setType(std::string type)
{
	_type.setType(type);
}

void StatsManager::setType(Pokemon *pkmn)
{
	_type.setType(pkmn->getType());
}

void StatsManager::setExpOnDeath(std::size_t value)
{
	_exp.setExpOnDeath(value);
}

void StatsManager::setEvolution(std::string str)
{
	Parser *parser = Parser::getInstance();
	std::pair<std::string, std::string> r;

	r = parser->splitStringToPair(str, '-');
	if (r.first == "" || r.first.find_first_not_of("0123456789") != std::string::npos)
		return;
	_pEvolve.first = std::stoi(r.first);
	_pEvolve.second = r.second;
}

std::size_t StatsManager::getBaseStat(const std::string stat) const
{
	if (_mBaseStat.find(stat) == _mStat.end())
		return 0;
	return _mBaseStat.at(stat);
}

std::size_t StatsManager::getIv(std::string iv) const
{
	if (_iv.find(iv) == _iv.end())
		return 0;
	return _iv.at(iv);
}

std::size_t StatsManager::getLvl() const
{
	return _exp.getLvl();
}

std::size_t StatsManager::getCurrentHp() const
{
	return _hp;
}

std::size_t &StatsManager::getrefCurrentHp()
{
	return _hp;
}

std::size_t StatsManager::getMaxHp() const
{
	return _maxHp;
}

std::size_t &StatsManager::getrefMaxHp()
{
	return _maxHp;
}

std::size_t StatsManager::getExpOnDeath() const
{
	return _exp.getExpOnDeath();
}

std::size_t StatsManager::getStat(std::string stat) const
{
	if (_mStat.find(stat) == _mStat.end())
		return 0;
	return (std::size_t)((float)_mStat.at(stat) * (this->getBuffMultiplier(stat)));
}

std::size_t StatsManager::getEvolveLvl() const
{
	return _pEvolve.first;
}

std::pair<Types, Types> StatsManager::getType() const
{
	return _type.getType();
}

float StatsManager::getDmgMultiplier() const
{
	return _dmgMultiplier;
}

std::string StatsManager::getEvolve() const
{
	return _pEvolve.second;
}

std::size_t &StatsManager::getrefCurrentExp()
{
	return _exp.getRefCurrentExp();
}

std::size_t &StatsManager::getrefNextLvlExp()
{
	return _exp.getRefNextLvlExp();
}

void StatsManager::setHost(Pokemon *pkmn)
{
	_host = pkmn;
}