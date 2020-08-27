//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// matrix.cpp
//

#include <iostream>

#include "Matrix.hpp"

Matrix::Matrix(std::map<std::string, Account *> accMap) : _accMap(accMap)
{
}

Matrix::~Matrix()
{
//	delete _matrix;
//	delete _linkMatrix;
}

void Matrix::createAdjacencyMatrix()
{
	std::size_t x = 0;
	std::size_t y = 0;
	std::string acc1;
	std::string acc2;
	
	while (x < _nbFriends) {
		while (y < _nbFriends) {
			acc1 = _names[x];
			acc2 = _names[y];
			_matrix[x][y] = ((_accMap[_names[x]])->isFriendWith(_names[y])) ? 1 : 0;
			y++;
		}
		y = 0;
		x++;
	}
}

void Matrix::floydWarshall()
{
	std::size_t i, j, k;

	for (i = 0; i < _nbFriends; i++)
		for (j = 0; j < _nbFriends; j++) {
			_linkMatrix[i][j] = _matrix[i][j];
		}
	for (k = 0; k < _nbFriends; k++) {
		for (i = 0; i < _nbFriends; i++) {
			for (j = 0; j < _nbFriends; j++) {
				if ((_linkMatrix[i][k] * _linkMatrix[k][j] != 0) && (i != j)) {
					if ((_linkMatrix[i][k] + _linkMatrix[k][j] < _linkMatrix[i][j]) || (_linkMatrix[i][j] == 0)) {
						
						_linkMatrix[i][j] = _linkMatrix[i][k] + _linkMatrix[k][j];
					}
				}
			}
		}
	}
}

void Matrix::createLinkMatrix()
{
	this->floydWarshall();
}

void Matrix::storeData()
{
	std::map<std::string, Account *>::iterator it = _accMap.begin();
	std::size_t i = 0;
	std::string tmp;

	while (it != _accMap.end()) {
		tmp = it->first;
		if (_nameToId.find(it->first) == _nameToId.end())
			_nameToId[tmp] = 0;
		it++;
	}
	std::map<std::string, std::size_t>::iterator it2;
	it2 = _nameToId.begin();
	while (it2 != _nameToId.end()) {
		_nameToId[it2->first] = i++;
		_names.push_back(it2->first);
		it2++;
	}
	_nbFriends = i;
	if (_nbFriends > 120)
		exit(0);
}

void Matrix::createMatrix()
{
	storeData();
	createAdjacencyMatrix();
	createLinkMatrix();
}

void Matrix::display(size_t n)
{
	std::map<std::string, Account*>::iterator it = _accMap.begin();
	std::size_t x = 0;
	std::size_t y = 0;

	while (it != _accMap.end()) {
		std::cout << it->first << std::endl;
		it++;
	}
	std::cout << std::endl;
	while (x < _nbFriends) {
		while (y < _nbFriends) {
			std::cout << _matrix[x][y] << ((y + 1 < _nbFriends) ? " " : "\n");
			y++;
		}
		y = 0;
		x++;
	}
	std::cout << std::endl;
	x = 0;
	y = 0;
	while (x < _nbFriends) {
		while (y < _nbFriends) {
			std::cout << ((_linkMatrix[x][y] <= n) ? _linkMatrix[x][y] : 0) << ((y + 1 < _nbFriends) ? " " : "\n");
			y++;
		}
		y = 0;
		x++;
	}
}
