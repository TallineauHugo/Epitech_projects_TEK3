//
// EPITECH PROJECT, 2018
// 303make
// File description:
// main
//

#include "Parser.hpp"
#include <iostream>
int main(int ac, char **av)
{
	Parser parser;

	switch (ac) {
	case 2:
		parser.parseFile(av[1]);
		parser.displayGraph();
		break;
	case 3:
		parser.parseFile(av[1]);
		return (parser.displayDependencies(av[2]));
	default:
		return 84;
	}
	return 0;
}
