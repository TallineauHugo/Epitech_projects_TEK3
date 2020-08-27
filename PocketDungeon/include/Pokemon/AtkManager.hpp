//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// atk
//

#pragma once

#include <map>
#include <vector>

#include "OtterEngine.hpp"

class Attack;
class Pokemon;

class AtkManager
{
public:
	AtkManager();
	~AtkManager();
public:
	void setHost(Pokemon *host);
	void setAtk(std::size_t slot, Attack *atk);
	void setMovepool(std::string str);
	void setMovepool(std::map<std::size_t, std::string> movepool);

	Attack *getAtk(std::size_t slot) const;
	float getAtkRange(std::size_t slot) const;
	std::map<std::size_t, std::string> getMovepool() const;

	void updateMoves(std::size_t lvl);
	bool tryLearnNewMove(std::string move);
	int attack(std::size_t slot, OtterEngine::Engine *oe, Vector2d velocity, Vector2d pos);

	bool haveAtk(std::string atkName) const;
private:
	Pokemon *_host;
	std::map<std::size_t, Attack*> _mAtk; //slot, atk
	std::map<std::size_t, std::string> _mAtkNameByLvl;
	std::map<std::size_t, float> _lastAtk;
	std::map<std::size_t, float> _cooldown;
	std::size_t _oldLvlCheck;
};
