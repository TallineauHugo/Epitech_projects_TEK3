//
// EPITECH PROJECT, 2018
// 304pacman
// File description:
// cell class declaration
//

#pragma once

#include <map>

#include "Type.hpp"

class Cell
{
public:
	Cell(Type type, std::pair<int, int> pos);
	~Cell() = default;

	Type getType() const;
	void setDist(size_t dist);
	size_t getDist() const;
	std::pair<int, int> getPos() const;
	void setVisited(bool visited);
	bool getVisited() const;

private:
	Type _type;
	size_t _dist;
	std::pair<int, int> _pos;
	bool _visited;
};