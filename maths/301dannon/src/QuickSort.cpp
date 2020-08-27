//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// Quicksort
//

#include "QuickSort.hpp"

QuickSort::QuickSort() : Sorter("quicksort")
{}

QuickSort::~QuickSort()
{}

void QuickSort::swap(std::vector<float> &tab, int first, int second)
{
	float tmp;

	tmp = tab[first];
	tab[first] = tab[second];
	tab[second] = tmp;
}

/*void QuickSort::quickSort(std::vector<float> &tab, int lo, int hi)
{
	int p;

	if (lo < hi) {
		p = partition(tab, lo, hi);
		quickSort(tab, lo, p - 1);
		quickSort(tab, p + 1, hi);
	}
	}*/

int QuickSort::quickSort(std::vector<float> &tab)
{
/*	int i = lo;
	int j = lo;
	float pivot = tab[hi];

	while (j < hi - 1) {
		_nbOp++;
		if (tab[j] < pivot) {
			this->swap(tab, i, j);
			i++;
		}
		j++;
	}
	this->swap(tab, i, hi);
	return i;*/
	if (tab.size() < 2)
		return 0;
	std::size_t pivot = 0;
	std::size_t n = 0;
	std::size_t i = 0;
	std::vector<float> left;
	std::vector<float> right;

	while (i < tab.size()) {
		if (i != pivot) {
			n++;
			_nbOp++;
			if (tab[i] < tab[pivot])
				left.push_back(tab[i]);
			if (tab[i] >= tab[pivot])
				right.push_back(tab[i]);
		}
		i++;
	}
	n += quickSort(left);
	n += quickSort(right);
	return n;
}

void QuickSort::sort(std::vector<float> tab)
{
	this->quickSort(tab);
}
