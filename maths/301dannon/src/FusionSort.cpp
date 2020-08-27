//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// Fusionsort
//

#include "FusionSort.hpp"

FusionSort::FusionSort() : Sorter("fusion sort")
{}

FusionSort::~FusionSort()
{}

std::vector<float> FusionSort::merge(std::vector<float> list1, std::vector<float> list2)
{

	std::vector<float> ret;

	while (list1.size() != 0 && list2.size() != 0) {
		_nbOp++;
		ret.push_back((list1[0] < list2[0]) ? list1[0] : list2[0]);
		((list1[0] < list2[0]) ? list1 : list2).erase((list1[0] < list2[0]) ? list1.begin() : list2.begin());
	}
	while (list1.size() != 0) {
		ret.push_back(list1.front());
		list1.erase(list1.begin());
	}
	while (list2.size() != 0) {
		ret.push_back(list2.front());
		list2.erase(list2.begin());
	}

	return ret;
}

std::vector<float> FusionSort::fusionSort(std::vector<float> list)
{
	std::size_t middle = list.size() / 2;
	
	if (list.size() == 0 || list.size() == 1)
		return list;
	std::vector<float> a(list.begin(), list.begin() + middle);
	std::vector<float> b(list.begin() + middle, list.end());
	std::vector<float> first = fusionSort(a);
	std::vector<float> second = fusionSort(b);
	std::vector<float> ret = merge(first, second);
	return ret;
}

void FusionSort::sort(std::vector<float> list)
{
	fusionSort(list);
}
