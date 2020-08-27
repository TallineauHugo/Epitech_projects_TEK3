//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// sorter
//

#pragma once

#include <vector>
#include <list>
#include <string>

class Sorter
{
public:
	Sorter(std::string sortName);
	virtual ~Sorter() = default;
public:
	virtual void sort(std::vector<float> tab) = 0;
	virtual void dispNbOp();
	virtual void resetNbOp();
	virtual std::vector<float> convertListToVector(std::list<float> list);
protected:
	std::size_t _nbOp;
	std::string _sortName;
};
