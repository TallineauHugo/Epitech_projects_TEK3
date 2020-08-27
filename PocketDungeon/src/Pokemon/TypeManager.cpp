//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// type manager
//

#include "TypeManager.hpp"
#include "TypeTable.hpp"

void TypeManager::setType(std::pair<Types, Types> types)
{
	_types = types;
}

void TypeManager::setType(std::string type)
{
	std::string subType;
	std::size_t pos;
	TypeTable *typeTable = TypeTable::getInstance();

	pos = type.find('/');
	subType = type.substr(0, pos);
	_types.first = typeTable->getType(subType);
	if (pos != std::string::npos) {
		subType = type.substr(pos + 1, std::string::npos);
		_types.second = typeTable->getType(subType);
	}
	else {
		_types.second = Types::NONE;
	}
}

std::pair<Types, Types> TypeManager::getType() const
{
	return _types;
}

TypeManager::TypeManager() : _types(std::make_pair(Types::NONE, Types::NONE))
{
}

TypeManager::~TypeManager()
{}
