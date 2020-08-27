//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// stats manager
//

#pragma once

#include <map>
#include "ExpManager.hpp"
#include "TypeManager.hpp"
#include "StatusManager.hpp"
#include "Types.hpp"

#define HP "hp"
#define ATK "atk"
#define DEF "def"
#define ATKSPE "atkSpe"
#define DEFSPE "defSpe"
#define SPEED "speed"

class Attack;
class Pokemon;

class StatsManager
{
public:
	StatsManager();
	~StatsManager();
public:
	//getters and setters
	void setDmgMultiplier(float value);
	void setBaseStat(std::pair<std::string, std::string> stat);
	void setIv(std::string stat, std::size_t value);
	void setType(std::string type);
	void setType(Pokemon *pkmn);
	void setExpOnDeath(std::size_t value);
	void setHost(Pokemon *pkmn);
	void setEvolution(std::string str);

	std::size_t getBaseStat(const std::string stat) const;
	std::size_t getIv(std::string iv) const;
	std::size_t getStat(std::string stat) const;
	std::size_t getLvl() const;
	std::size_t getCurrentHp() const;
	std::size_t &getrefCurrentHp();
	std::size_t getMaxHp() const;
	std::size_t &getrefMaxHp();
	std::size_t getExpOnDeath() const;
	std::size_t getEvolveLvl() const;
	std::size_t& getrefCurrentExp();
	std::size_t& getrefNextLvlExp();
	std::pair<Types, Types> getType() const;
	float getDmgMultiplier() const;
	std::string getEvolve() const;

	//management
	void updateStats();
	void heal(std::size_t amount);
	void lvlUp();
	void gainExp(std::size_t amount);
	void gainEv(std::string type, std::size_t amount);
	void update(float deltaTime);
	void applyBuff(std::string stat, int lvlToAdd);

	bool loseLife(std::size_t amount);
	bool takeDamage(Attack atk);
	bool applyStatusFor(Status::Status status, float seconds);
	bool canMove() const;
	bool haveStatus(Status::Status status) const;
	float getBuffMultiplier(std::string stat) const;

private:
	ExpManager _exp;
	TypeManager _type;
	Status::StatusManager _status;
	std::map<std::string, std::size_t> _mBaseStat;
	std::map<std::string, std::size_t> _mStat;
	std::map<std::string, std::size_t> _ev;
	std::map<std::string, std::size_t> _iv;
	std::map<std::string, int> _mBuffLevel;
	std::map<int, float> _mBuffMultiplier;
	std::pair<std::size_t, std::string> _pEvolve;
	std::size_t _totalEv;
	std::size_t _hp;
	std::size_t _maxHp;
	float _dmgMultiplier;
	Pokemon *_host;
};
