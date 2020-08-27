//
// EPITECH PROJECT, 2018
// 304pacman
// File description:
// map class implementation
//

#include <fstream>
#include <iostream>
#include <algorithm>

#include "macros.hpp"
#include "Map.hpp"

Map::Map()
{
	_types['0'] = EMPTY;
	_types['1'] = WALL;
	_types['F'] = GHOST;
	_types['P'] = PACMAN;
	_chars[GHOST] = 'F';
	_chars[PACMAN] = 'P';
	_mapSize = std::make_pair(0, 0);
	_minDist = INFINTE;
	_foundPacman = false;
	_foundGhost = false;
}

Map::~Map()
{
	for (auto elem: _cells)
		delete elem.second;
}

bool Map::loadFromMap(std::string filename)
{
	std::ifstream infile(filename);
	std::string line;
	int x;
	int y = 0;

	if (!infile.good())
		return false;
	while (std::getline(infile, line)) {
		x = 0;
		if (!line.empty()) {
			for (char c: line) {
				_cells[std::make_pair(x, y)] = new Cell(
					_types[c], std::make_pair(x, y));
				if (c == _chars[GHOST]) {
					if (_foundGhost)
						return false;
					_foundGhost = true;
					_ghostPos = std::make_pair(x, y);
					_cells[std::make_pair(x, y)]->setDist(
						0);
				} else if (c == _chars[PACMAN]) {
					if (_foundPacman)
						return false;
					_foundPacman = true;
					_pacmanPos = std::make_pair(x, y);
				}
				x++;
			}
			if (x > _mapSize.first)
				_mapSize.first = x;
			y++;
		}
	}
	_mapSize.second = y;
	return _foundGhost && _foundPacman;
}

bool Map::setChars(std::string wall, std::string empty)
{
	if (empty.length() != 1 || wall.length() != 1)
		return false;
	_chars[EMPTY] = empty[0];
	_chars[WALL] = wall[0];
	return true;
}

void Map::display()
{
	int x = 0;
	int y = 0;
	std::pair<int, int> cellPos = std::make_pair(x, y);

	while (y < _mapSize.second) {
		x = 0;
		cellPos.second = y;
		while (x < _mapSize.first) {
			cellPos.first = x;
			if (_cells[cellPos]->getType() != EMPTY || _cells[cellPos]->getDist() > _minDist || _cells[cellPos]->getDist() == INFINTE)
				std::cout << _chars[_cells[cellPos]->getType()];
			else
				std::cout << _cells[cellPos]->getDist() % 10;
			x++;
		}
		y++;
		std::cout << std::endl;
	}
}

Cell *Map::getNeighbour(Cell *target, Direction dir)
{
	std::pair<int, int> pos = target->getPos();

	if (dir == NORTH && pos.second > 0) {
		pos.second--;
		return _cells[pos];
	}
	else if (dir == EAST && pos.first < _mapSize.first) {
		pos.first++;
		return _cells[pos];
	}
	else if (dir == SOUTH && pos.second < _mapSize.second) {
		pos.second++;
		return _cells[pos];
	}
	else if (dir == WEST && pos.first > 0) {
		pos.first--;
		return _cells[pos];
	}
	return nullptr;
}

void Map::fillDists()
{
	static std::vector<Cell*> cells;
	static size_t currentDist = 1;
	std::vector<Cell*> tmp;
	Cell *check;
	Cell *north;
	Cell *east;
	Cell *south;
	Cell *west;

	if (cells.empty()) {
		_cells[_ghostPos]->setVisited(true);
		if ((north = getNeighbour(_cells[_ghostPos], NORTH)) != nullptr) {
			addToList(cells, north);
			north->setVisited(true);
			north->setDist(1);
			if (north == _cells[_pacmanPos])
				return;
		}
		if ((east = getNeighbour(_cells[_ghostPos], EAST)) != nullptr) {
			addToList(cells, east);
			east->setVisited(true);
			east->setDist(1);
			if (east == _cells[_pacmanPos])
				return;
		}
		if ((south = getNeighbour(_cells[_ghostPos], SOUTH)) != nullptr) {
			addToList(cells, south);
			south->setVisited(true);
			south->setDist(1);
			if (south == _cells[_pacmanPos])
				return;
		}
		if ((west = getNeighbour(_cells[_ghostPos], WEST)) != nullptr) {
			addToList(cells, west);
			west->setVisited(true);
			west->setDist(1);
			if (west == _cells[_pacmanPos])
				return;
		}
	}
	while (!cells.empty()) {
		check = cells.at(0);
		cells.erase(cells.begin());
		if (check && !check->getVisited()) {
			check->setDist(currentDist + 1);
			addToList(tmp, check);
			check->setVisited(true);
		}
		if (check && check->getPos() == _pacmanPos)
			return;
	}
	currentDist++;
	cells = tmp;
	if (!cells.empty())
		fillDists();
}

void Map::addToList(std::vector<Cell *> &list, Cell *target)
{
	Cell *neighbour = nullptr;
	
	if (target->getType() == EMPTY) {
		neighbour = getNeighbour(target, NORTH);
		if (std::find(list.begin(), list.end(), neighbour) == list.end())
			list.push_back(neighbour);
		
		neighbour = getNeighbour(target, EAST);
		if (std::find(list.begin(), list.end(), neighbour) == list.end())
			list.push_back(neighbour);

		neighbour = getNeighbour(target, SOUTH);
		if (std::find(list.begin(), list.end(), neighbour) == list.end())
			list.push_back(neighbour);

		neighbour = getNeighbour(target, WEST);
		if (std::find(list.begin(), list.end(), neighbour) == list.end())
			list.push_back(neighbour);
	}
}

std::pair<int, int> Map::getSize() const
{
	return this->_mapSize;
}
