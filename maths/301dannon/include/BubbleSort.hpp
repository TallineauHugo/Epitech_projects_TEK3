//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// BubbleSort
//

#pragma once

#include "Sorter.hpp"

class BubbleSort : virtual public Sorter
{
public:
	BubbleSort();
	~BubbleSort();
public:
	void sort(std::vector<float> tab);
};
