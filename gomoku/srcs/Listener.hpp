//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// listener class declaration
//

#pragma once

#include <map>

#include "IBrain.hpp"


class Listener
{
	typedef int (Listener::*fptr)(std::string);
public:
	Listener(IBrain *brain);

	void run();

private:
	int start(std::string str);
	int turn(std::string str);
	int begin(std::string ignored);
	int board(std::string str);
	int end(std::string ignored);

private:
	IBrain *_brain;
	std::map<std::string, fptr> _methMap;
};
