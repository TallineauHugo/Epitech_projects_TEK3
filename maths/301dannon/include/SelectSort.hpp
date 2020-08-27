//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// SelectSort
//

#pragma once

#include "Sorter.hpp"

class SelectSort : virtual public Sorter
{
public:
	SelectSort();
	~SelectSort();
public:
	void sort(std::vector<float> tab);
};
