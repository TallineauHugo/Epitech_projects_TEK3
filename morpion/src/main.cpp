//
// EPITECH PROJECT, 2018
// morpion
// File description:
// main
//

#include "Morpion.hpp"

int main()
{
	srand(time(NULL));
	Morpion *morpion = new Morpion(3);

	morpion->start();
	return 0;
}
