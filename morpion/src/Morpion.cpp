//
// EPITECH PROJECT, 2018
// morpion
// File description:
// morpion
//

#include <unistd.h>
#include <iostream>

#include "AI.hpp"
#include "Morpion.hpp"

Morpion::Morpion(int boardSize) : _size(boardSize), ai(nullptr)
{
	ai = new AI(boardSize);
}

Morpion::~Morpion()
{}

void Morpion::start()
{
	std::pair<int, int> move;
	bool loop = false;

	std::cout << "Hi ! You play first and with the X symbol, have fun !" << std::endl;
	
	ai->displayBoard();
	while (ai->winner() == 0) {
		loop = false;
		while (loop == false) {
			std::cout << "Please enter x (hor.) between [1 - 3]" << std::endl;
			std::cin >> move.first;
			std::cout << "Please enter y (vert.) between [1 - 3]" << std::endl;
			std::cin >> move.second;
			loop = ai->putPiece(move.first - 1, move.second - 1, 2);
			if (loop == false)
				std::cout << "Invalid move, try again...\n";
		}
		ai->displayBoard();
		if (ai->winner() != 0)
			break;
		move = ai->play(5);
		ai->putPiece(move.first, move.second, 1);
		ai->displayBoard();
	}
	int winner = ai->winner();

	switch (winner) {
	case 1:
		std::cout << "AI won ez pz";
		break;
	case 2:
		std::cout << "GG human !";
		break;
	case 3:
		std::cout << "TIE";
		break;
	}
	std::cout << std::endl;
}
