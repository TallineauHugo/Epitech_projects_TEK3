//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// atk facto
//

#include "AtkFactory.hpp"
#include "Growl.hpp"
#include "Tackle.hpp"
#include "ThunderShock.hpp"
#include "VineWhip.h"

AtkFactory::AtkFactory()
{
	_mAtks[GROWL] = new Growl(nullptr);
	_mAtks[TACKLE] = new Tackle(nullptr);
	_mAtks[THUNDERSHOCK] = new ThunderShock(nullptr);
	_mAtks[VINEWHIP] = new VineWhip(nullptr);
}

Attack *AtkFactory::generateAtk(std::string atk) const
{
	if (_mAtks.find(atk) == _mAtks.end())
		return nullptr;
	return _mAtks.at(atk);
}