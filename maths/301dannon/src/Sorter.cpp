//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// sorter
//

#include <iostream>
#include "Sorter.hpp"

Sorter::Sorter(std::string sortName) : _nbOp(0), _sortName(sortName)
{}

void Sorter::dispNbOp()
{
	std::cout << _sortName << ": " << _nbOp << " comparison" << ((_nbOp <= 1) ? "" : "s") << std::endl;
	_nbOp = 0;
}

void Sorter::resetNbOp()
{
	_nbOp = 0;
}

std::vector<float> Sorter::convertListToVector(std::list<float> list)
{
	std::list<float>::iterator it = list.begin();
	std::vector<float> tab;

	while (it != list.end()) {
		tab.push_back(*it);
		it++;
	}
	return tab;
}
