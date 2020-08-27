//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// Bubblesort
//

#include "BubbleSort.hpp"

BubbleSort::BubbleSort() : Sorter("bubble sort")
{}

BubbleSort::~BubbleSort()
{}

void BubbleSort::sort(std::vector<float> tab)
{
	std::size_t i = 0;
	std::size_t offset = 0;
	std::size_t length = tab.size();
	float tmp;

	while (offset < length) {
		while (i < (length - 1 - offset)) {
			_nbOp += 1;
			if (tab[i] > tab[i + 1]) {
				tmp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = tmp;
			}
			i++;
		}
		i = 0;
		offset++;
	}
}
