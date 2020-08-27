//
// EPITECH PROJECT, 2018
// 304pacman
// File description:
// cell class implementation
//

#include <iostream>

#include "macros.hpp"
#include "Cell.hpp"

Cell::Cell(Type type, std::pair<int, int> pos): _type(type), _dist(INFINTE), _pos(pos), _visited(false)
{
}

Type Cell::getType() const
{
	return _type;
}

void Cell::setDist(size_t dist)
{
	_dist = dist;
}

size_t Cell::getDist() const
{
	return _dist;
}

std::pair<int, int> Cell::getPos() const
{
	return _pos;
}

void Cell::setVisited(bool visited)
{
	_visited = visited;
}

bool Cell::getVisited() const
{
	return _visited;
}
