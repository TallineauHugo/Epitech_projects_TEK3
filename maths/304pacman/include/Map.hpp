//
// EPITECH PROJECT, 2018
// 304pacman
// File description:
// map class declaration
//

#pragma once

#include <map>
#include <vector>

#include "Cell.hpp"
#include "Directon.hpp"

class Map
{
public:
	Map();
	~Map();

	bool loadFromMap(std::string filename);
	bool setChars(std::string wall, std::string empty);
	void display();
	void fillDists();

	std::pair<int, int> getSize() const;

private:
	Cell *getNeighbour(Cell *target, Direction dir);
	void addToList(std::vector<Cell*> &list, Cell *target);

private:
	bool _foundGhost;
	bool _foundPacman;
	std::map<std::pair<int, int>, Cell*> _cells;
	std::map<char, Type> _types;
	std::map<Type, char> _chars;
	std::pair<int, int> _mapSize;
	std::pair<int, int> _ghostPos;
	std::pair<int, int> _pacmanPos;
	size_t _minDist;
};
