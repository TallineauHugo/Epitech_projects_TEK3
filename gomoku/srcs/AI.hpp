//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// AI
//

#pragma once

#include <vector>
#include <tuple>

#include "IBrain.hpp"
#include "Brain.hpp"

class Board;

class AI : public IBrain
{
public:
	AI();
	~AI();
public:
	bool start(int boardSize);
	std::pair<int, int> turn(int x, int y);
	std::pair<int, int> begin();
	std::pair<int, int> board(std::vector<std::tuple<int, int, int>> arg);
	bool end();
	
private:
private:
	int _boardSize;
	bool _black;
	Board *_board;
	Brain *_brain;
};
