//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// atk facto
//

#pragma once

#include "Attack.hpp"

#define GROWL "Growl"
#define TACKLE "Tackle"
#define THUNDERSHOCK "ThunderShock"
#define VINEWHIP "VineWhip"

class AtkFactory
{
public:
	AtkFactory();
	~AtkFactory() = default;
public:
	Attack *generateAtk(std::string atk) const;
private:
	std::map<std::string, Attack*> _mAtks;
};