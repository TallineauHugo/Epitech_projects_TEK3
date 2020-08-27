//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// type manager
//

#pragma once

#include "Types.hpp"

#include <utility>
#include <string>

class TypeManager
{
public:
	TypeManager();
	~TypeManager();
public:
	void setType(std::string type);
	void setType(std::pair<Types, Types> types);
	
	std::pair<Types, Types> getType() const;
private:
	std::pair<Types, Types> _types;
};
