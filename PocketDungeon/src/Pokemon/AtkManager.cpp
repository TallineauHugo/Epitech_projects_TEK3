//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// atk manager
//

#include <iostream>
#include "AtkManager.hpp"
#include "Tackle.hpp"
#include "Attack.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"
#include "Parser.hpp"
#include "AtkFactory.hpp"
#include "Pokemon.hpp"

void AtkManager::setAtk(std::size_t slot, Attack *atk)
{
	if (slot > 3)
		return;
	if (_mAtk.find(slot) != _mAtk.end() && _mAtk[slot] != nullptr)
		delete _mAtk[slot];
	_mAtk[slot] = atk;
}

void AtkManager::setMovepool(std::map<std::size_t, std::string> movepool)
{
	_mAtkNameByLvl = movepool;
}

void AtkManager::setMovepool(std::string str)
{
	std::size_t size;
	std::vector<std::string> vToks;
	std::pair<std::string, std::string> link;
	Parser *parser = Parser::getInstance();

	vToks = parser->splitStringToVector(str, '/');
	size = vToks.size();
	for (std::size_t i = 0; i < size; i++) {
		link = parser->splitStringToPair(vToks[i], '-');
		_mAtkNameByLvl[std::stoi(link.first)] = link.second;
	}
}

void AtkManager::updateMoves(std::size_t lvl)
{
	if (lvl == _oldLvlCheck) {
		return;
	}
	_oldLvlCheck = lvl;
	if (_mAtkNameByLvl.find(lvl) != _mAtkNameByLvl.end() &&
		this->haveAtk(_mAtkNameByLvl[lvl]) == false) {
		this->tryLearnNewMove(_mAtkNameByLvl[lvl]);
	}
}

bool AtkManager::tryLearnNewMove(std::string move)
{
	std::cout << "LEARN NEW ATK:" << move << std::endl;
	AtkFactory facto;
	Attack *atk;

	atk = facto.generateAtk(move);
	if (!atk)
		return false;

	for (std::size_t i = 0; i < 4; i++) {
		if (_mAtk.find(i) == _mAtk.end() || _mAtk.at(i) == nullptr) {
			atk->setHost(_host);
			this->setAtk(i, atk);
			return true;
		}
	}
	//on remplace un spell random pour le moment
	this->setAtk(rand() % 4, atk);
	return true;
	//voir pour laisser le choix au joueur
}

bool AtkManager::haveAtk(std::string atkName) const
{
	for (std::size_t i = 0; i < 4; i++) {
		if (_mAtk.at(i) && _mAtk.at(i)->getName() == atkName)
			return true;
	}
	return false;
}

Attack *AtkManager::getAtk(std::size_t slot) const
{
	if (slot > 3 || _mAtk.find(slot) == _mAtk.end())
		return nullptr;
	return _mAtk.at(slot);
}

float AtkManager::getAtkRange(std::size_t slot) const
{
	if (slot > 3 || _mAtk.find(slot) == _mAtk.end())
		return -1.0;
	if (_mAtk.at(slot) == nullptr)
		return -1.0;
	return _mAtk.at(slot)->getRange();
}

std::map<std::size_t, std::string> AtkManager::getMovepool() const
{
	return _mAtkNameByLvl;
}

int AtkManager::attack(std::size_t slot, OtterEngine::Engine *oe, Vector2d velocity, Vector2d pos)
{
	Attack *rawAttack = this->getAtk(slot);
	OtterEngine::Object *atk;
	if (!rawAttack)
		return 1;

	float elapsedTime = TimeManager::getInstance()->getTotalTime();

	if (_lastAtk[slot] > elapsedTime || elapsedTime - _lastAtk[slot] > _cooldown[slot]) {
		atk = rawAttack->clone(rawAttack, velocity, pos);
		oe->_sm.addSound("ressources/sounds/" + dynamic_cast<Attack *>(atk)->getAtkName() + "_attack.wav");
		oe->addObject(atk);
		_lastAtk[slot] = elapsedTime;
		return 0;
	}
	return 1;
}

void AtkManager::setHost(Pokemon *pkmn)
{
	_host = pkmn;
}

AtkManager::AtkManager()
{
	_mAtk[0] = nullptr;
	_mAtk[1] = nullptr;
	_mAtk[2] = nullptr;
	_mAtk[3] = nullptr;

	_lastAtk[0] = 0.0;
	_lastAtk[1] = 0.0;
	_lastAtk[2] = 0.0;
	_lastAtk[3] = 0.0;

	_cooldown[0] = 1.5;
	_cooldown[1] = 1.5;
	_cooldown[2] = 1.5;
	_cooldown[3] = 1.5;

	_oldLvlCheck = 0;
}

AtkManager::~AtkManager()
{
}
