//
// EPITECH PROJECT, 2018
// maths
// File description:
// maths
//

#include <iostream>

void displayUsage(std::string bin)
{
	std::cout << "USAGE\n\t" << bin << " n ir jr [i j]\n\n";
	std::cout << "DESCRIPTION\n";
	std::cout << "    n\t\t\tsize of the room\n";
	std::cout << "    (ir, jr)\t\tcoordinates of the radiator\n";
	std::cout << "    (i, j)\t\tcoordinates of a point in the room\n";
}

int main(int ac, char **av)
{
	std::string str;

	for (int i = 0; i < ac; i++) {
		str = std::string(av[i]);
		if (str.compare(0, 2, "-h") == 0) {
			displayUsage(av[0]);
			return 0;
		}
	}
	if (ac != 4 && ac != 6)
		return 84;
	return 0;
}
