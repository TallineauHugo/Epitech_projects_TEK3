//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// AI
//

#include <iostream>

#include "AI.hpp"
#include "Board.hpp"
#include "GomokuMacro.hpp"

AI::AI() : _boardSize(20), _board(nullptr), _brain(nullptr)
{
}

AI::~AI()
{
	delete _board;
}

bool AI::start(int boardSize)
{
	_board = new Board;
	_brain = new Brain(_board);

	_boardSize = boardSize;
	if (_board->setSize(boardSize) == false)
		return false;
	_board->reset();
	_brain->setSize(boardSize);
	return true;
}

std::pair<int, int> AI::turn(int x, int y)
{
	std::pair<int, int> move = std::make_pair(-1, -1);
	bool ret;

	if (!_board) {
		std::cout << "Must call START before anything else";
		return move;
	}
	ret = _board->setCell(x, y, FOE);
	_brain->addArea(x, y, FOE);
	if (ret == false) {
		std::cout << "Enemy made forbidden move, cannot process";
		return move;
	}

	move = _brain->process(1);
	_board->setCell(move.first, move.second, OWN);
	_brain->addArea(move.first, move.second, OWN);
	return move;
}

std::pair<int, int> AI::begin()
{
	std::pair<int, int> move = std::make_pair(this->_boardSize / 2, this->_boardSize / 2);

	_board->setCell(move.first, move.second, OWN);
	_brain->addArea(move.first, move.second, OWN);
	return move;
}

std::pair<int, int> AI::board(std::vector<std::tuple<int, int, int>> arg)
{
	std::pair<int, int> move = std::make_pair(0, 0);
	std::vector<std::tuple<int, int, int>>::iterator it = arg.begin();

	_board->reset();

	while (it != arg.end()) {
		_board->setCell(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
		_brain->addArea(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
		it++;
	}

	move = _brain->process(2);
	_board->setCell(move.first, move.second, OWN);
	_brain->addArea(move.first, move.second, OWN);
	return move;
}

bool AI::end()
{
	this->_brain->end();
	return true;
}
