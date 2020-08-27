//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// Selectsort
//

#include "SelectSort.hpp"

SelectSort::SelectSort() : Sorter("select sort")
{}

SelectSort::~SelectSort()
{}

void SelectSort::sort(std::vector<float> tab)
{
	std::size_t i = 0;
	std::size_t j;
	std::size_t length = tab.size();
	std::size_t min;
	float tmp;

	while (i < length - 1) {
		min = i;
		j = i + 1;
		while (j < length) {
			_nbOp++;
			if (tab[j] < tab[min])
				min = j;
			j++;
		}
		if (min != i) {
			tmp = tab[min];
			tab[min] = tab[i];
			tab[i] = tmp;
		}
		i++;
	}
}
