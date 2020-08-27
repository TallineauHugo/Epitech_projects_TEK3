//
// EPITECH PROJECT, 2018
// 304pacman
// File description:
// main
//

#include <iostream>

#include "Map.hpp"

void usage(char *name)
{
	std::cout << name << " file c1 c2" << std::endl;
	std::cout << "\tfile\trepresents the game board" << std::endl;
	std::cout << "\tc1\tcharacter to be displayed for a wall" << std::endl;
	std::cout << "\tc2\tcharacter to be displayed for an empty space" << std::endl;
}

int main(int ac, char **av)
{
	Map map;

	if (ac != 4) {
		usage(av[0]);
		return 84;
	}
	if (!map.loadFromMap(av[1]))
		return 84;
	if (!map.setChars(av[2], av[3]))
		return 84;
//	if (map.getSize().first >= 47 && map.getSize().second >= 47)
//		return 0;
	map.fillDists();
	map.display();
	return 0;
}
