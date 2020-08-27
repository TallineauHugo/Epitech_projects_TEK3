//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// type tabl
//

#include "TypeTable.hpp"
#include "Parser.hpp"
#include <vector>
#include <iostream>

float TypeTable::getMultiplier(std::pair<Types, Types> types, Types foe) const
{
	return _multipliers.at(foe).at(types.first) * _multipliers.at(foe).at(types.second);
}

Types TypeTable::getType(std::string string) const
{
	if (_mStringToType.find(string) != _mStringToType.end())
		return _mStringToType.at(string);
	return Types::NONE;
}

std::string TypeTable::getType(Types type) const
{
	if (_mTypeToString.find(type) != _mTypeToString.end())
		return _mTypeToString.at(type);
	return "none";
}

void TypeTable::initMap()
{
	_mStringToType["normal"] = Types::NORMAL;
	_mStringToType["fighting"] = Types::FIGHTING;
	_mStringToType["flying"] = Types::FLYING;
	_mStringToType["poison"] = Types::POISON;
	_mStringToType["ground"] = Types::GROUND;
	_mStringToType["rock"] = Types::ROCK;
	_mStringToType["bug"] = Types::BUG;
	_mStringToType["ghost"] = Types::GHOST;
	_mStringToType["steel"] = Types::STEEL;
	_mStringToType["fire"] = Types::FIRE;
	_mStringToType["water"] = Types::WATER;
	_mStringToType["grass"] = Types::GRASS;
	_mStringToType["electric"] = Types::ELECTRIC;
	_mStringToType["psy"] = Types::PSY;
	_mStringToType["ice"] = Types::ICE;
	_mStringToType["dragon"] = Types::DRAGON;
	_mStringToType["fairy"] = Types::FAIRY;
	_mStringToType["none"] = Types::NONE;

	_mTypeToString[Types::NORMAL] = "normal";
	_mTypeToString[Types::FIGHTING] = "fighting";
	_mTypeToString[Types::FLYING] = "flying";
	_mTypeToString[Types::POISON] = "poison";
	_mTypeToString[Types::GROUND] = "ground";
	_mTypeToString[Types::ROCK] = "rock";
	_mTypeToString[Types::BUG] = "bug";
	_mTypeToString[Types::GHOST] = "ghost";
	_mTypeToString[Types::STEEL] = "steel";
	_mTypeToString[Types::FIRE] = "fire";
	_mTypeToString[Types::WATER] = "water";
	_mTypeToString[Types::GRASS] = "grass";
	_mTypeToString[Types::ELECTRIC] = "electric";
	_mTypeToString[Types::PSY] = "psy";
	_mTypeToString[Types::ICE] = "ice";
	_mTypeToString[Types::DRAGON] = "dragon";
	_mTypeToString[Types::FAIRY] = "fairy";
	_mTypeToString[Types::NONE] = "none";
}

bool TypeTable::initMultiplier()
{
	std::pair<std::string, std::string> typeAndStats;
	std::vector<std::string> types;
	std::vector<std::string> stats;
	std::vector<std::string> vTokens;
	Parser *parser = Parser::getInstance();
	std::string buff;
	std::size_t nbLine;
	std::size_t nbTypes;
	Types type1;
	Types type2;
	float eff;

	_mEffectiveness["I"] = 0.0;
	_mEffectiveness["NE"] = 0.5;
	_mEffectiveness["E"] = 1.0;
	_mEffectiveness["SE"] = 2.0;

	if (!parser->readFileByName("ressources/typeMultiplier.dont_touch", buff)) {
		std::cout << "You must execute the binary from root for the moment (oopsi exit 84)" << std::endl;
		exit(84);
	}
	vTokens = parser->splitStringToVector(buff, '\n');
	types = parser->splitStringToVector(vTokens[0], '|');

	nbLine = vTokens.size();
	for (std::size_t i = 1; i < nbLine; i++) {
		typeAndStats = parser->splitStringToPair(vTokens[i], ':');
		stats = parser->splitStringToVector(typeAndStats.second, '|');
		nbTypes = stats.size();
		type1 = this->getType(typeAndStats.first);
		for (std::size_t y = 0; y < nbTypes; y++) {	
			type2 = this->getType(types[y]);
			eff = _mEffectiveness[stats[y]];
			_multipliers[type1][type2] = eff;
		}
	}
}

TypeTable::TypeTable()
{
	initMap();
	initMultiplier();
}

TypeTable::~TypeTable()
{}
