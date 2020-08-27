//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// InsertionSort
//

#pragma once

#include "Sorter.hpp"

class InsertionSort : virtual public Sorter
{
public:
	InsertionSort();
	~InsertionSort();
public:
	void sort(std::vector<float> list);
};
