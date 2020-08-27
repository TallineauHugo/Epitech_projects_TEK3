//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// main
//

#include "Parser.hpp"
#include <iostream>
int main(int ac, char **av)
{
	Parser parser;

	if (ac != 3 && ac != 4)
		return 84;
	parser.parseFile(av[1]);
	
	if (ac == 3) {
		std::string str(av[2]);
		if (str.find_first_not_of("0123456789") != std::string::npos)
			exit(84);
		parser.displayFull(atoi(av[2]));
	}
	else {
		std::string str2(av[2]);
		std::string str3(av[3]);
		if (str2.find_first_not_of("0123456789") == std::string::npos ||
		    str3.find_first_not_of("0123456789") == std::string::npos)
			return 84;
		parser.displayLinkBetween(av[2], av[3]);
	}
	return 0;
}
