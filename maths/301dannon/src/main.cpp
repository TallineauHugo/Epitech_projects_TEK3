//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// main.cpp
//

#include <iostream>
#include <cstring>
#include "SelectSort.hpp"
#include "InsertionSort.hpp"
#include "BubbleSort.hpp"
#include "FusionSort.hpp"
#include "QuickSort.hpp"
#include "ListFactory.hpp"

void usage(char *name)
{
	std::cout << "USAGE" << std::endl;
	std::cout << "\t" << name << " file" << std::endl;
	std::cout << std::endl << "DESCRIPTION" << std::endl;
	std::cout << "\tfile\tfile that contains the numbers to be sorted,";
	std::cout << " seperated by spaces" << std::endl;
}

static void process(std::vector<float> list)
{
	Sorter *sorter = new SelectSort;

	std::cout << list.size() << " element" << ((list.size() > 1) ? "s":"") << std::endl;

	sorter->sort(list);
	sorter->dispNbOp();
	delete sorter;

	sorter = new InsertionSort;
	sorter->sort(list);
	sorter->dispNbOp();
	delete sorter;

	sorter = new BubbleSort;
	sorter->sort(list);
	sorter->dispNbOp();
	delete sorter;

	sorter = new FusionSort;
	sorter->sort(list);
	sorter->dispNbOp();
	delete sorter;

	sorter = new QuickSort;
	sorter->sort(list);
	sorter->dispNbOp();
	delete sorter;
}

int main(int ac, char **av)
{
	ListFactory listFactory;
	std::vector<float> list;

	if (ac != 2) {
		usage(av[0]);
		return 84;
	}
	else if (!strcmp(av[1], "-h")) {
		usage(av[0]);
		return 0;
	}
	list = listFactory.getListFromFile(av[1]);
	if (listFactory.failed() || list.empty())
		return 84;
	process(list);
	return 0;
}
