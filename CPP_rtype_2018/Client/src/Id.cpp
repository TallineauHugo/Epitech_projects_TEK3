//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// id
//

#include "Id.hpp"

Id::Id() : _id(4)
{}

Id::~Id()
{}

std::size_t Id::getNextId()
{
	return _id++;
}