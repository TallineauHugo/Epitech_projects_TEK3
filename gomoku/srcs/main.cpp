//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// main
//

#include "Listener.hpp"
#include "AI.hpp"

int main()
{
	AI ai;
	Listener listener(&ai);

	listener.run();
	return 0;
}