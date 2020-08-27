//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// type table
//

#pragma once

#include <map>
#include "Types.hpp"

class TypeTable
{
public:
	static TypeTable *getInstance() {
		static TypeTable instance;

		return &instance;
	}
	~TypeTable();
public:

	Types getType(std::string string) const;
	std::string getType(Types) const;
	float getMultiplier(std::pair<Types, Types> types, Types foe) const;
private:
	TypeTable();
	void initMap();
	bool initMultiplier();
private:
	std::map<std::string, Types> _mStringToType;
	std::map<Types, std::string> _mTypeToString;
	std::map<Types, std::map<Types, float>> _multipliers;
	std::map<std::string, float> _mEffectiveness;
};
