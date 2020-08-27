//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// QuickSort
//

#pragma once

#include "Sorter.hpp"

class QuickSort : virtual public Sorter
{
public:
	QuickSort();
	~QuickSort();
public:
	void sort(std::vector<float> tab);
private:
	int quickSort(std::vector<float> &tab);
//	int partition(std::vector<float> &tab);
	void swap(std::vector<float> &tab, int first, int second);
};
