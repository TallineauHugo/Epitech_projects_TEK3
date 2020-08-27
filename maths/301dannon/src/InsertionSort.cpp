//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// InsertionSort
//

#include "InsertionSort.hpp"

InsertionSort::InsertionSort() : Sorter("insertion sort")
{}

InsertionSort::~InsertionSort()
{}

void InsertionSort::sort(std::vector<float> tab)
{
	std::vector<float> tab2;
	std::size_t i = 0;
	std::size_t j;
	std::size_t idx = 0;
	std::size_t length = tab.size();
	bool success;

	while (i < length) {
		idx = 0;
		success = false;
		j = 0;
		while (j < tab2.size()) {
			_nbOp++;
			if (tab2[j] > tab[i]) {
				tab2.insert(tab2.begin() + idx, tab[i]);
				success = true;
				break;
			}
			idx++;
			j++;
		}
		if (success == false)
			tab2.push_back(tab[i]);
		i++;
	}
}
