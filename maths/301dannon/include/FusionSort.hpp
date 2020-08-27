//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// FusionSort
//

#pragma once

#include "Sorter.hpp"

class FusionSort : virtual public Sorter
{
public:
	FusionSort();
	~FusionSort();
public:
	void sort(std::vector<float> tab);
private:
	std::vector<float> merge(std::vector<float> list1, std::vector<float> list2);
	std::vector<float> fusionSort(std::vector<float> list);
};
