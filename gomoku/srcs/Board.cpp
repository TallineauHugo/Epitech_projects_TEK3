//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// board
//

#include <iostream>
#include <vector>
#include <mutex>

#include "Board.hpp"
#include "Cell.hpp"
#include "GomokuMacro.hpp"

Board::Board() : _boardSize(20), _winner(0), _board(nullptr)
{}

Board::~Board()
{
	if (_board)
		delete _board;
}

bool Board::setSize(int boardSize)
{
	if (boardSize < 5)
		return false;
	_boardSize = boardSize;
	return true;
}

bool Board::setCell(int x, int y, int value)
{
	_board[x][y].setValue(value);
//	if (value != CELL_EMPTY)
//		this->checkWin(x, y, value);
//	else
//		_winner = 0;
	return true;
}

int Board::winner() const
{
	if (this->getNbPieces() >= _boardSize * _boardSize)
		return 3;
	return _winner;
}

void Board::checkWin(int i, int j, int id)
{
	int ret = id;
	std::vector<int> count;
	int x = i;
	int y = j;

	for (int z = 0; z <= 8; z++)
		count.insert(count.begin() + z, 0);
	//N
	while (x >= 0 && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[N] += 1;
		x--;
	}
	x = i;
	ret = id;

	//NE
	while (y < _boardSize && x >= 0 && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[NE] += 1;
		y++;
		x--;
	}
	x = i;
	y = j;
	ret = id;


	//E
	while (y < _boardSize && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[E] += 1;
		y++;
	}
	y = j;
	ret = id;

	//SE
	while (y < _boardSize && x < _boardSize && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[SE] += 1;
		y++;
		x++;
	}
	x = i;
	y = j;
	ret = id;

	//S
	while (x < _boardSize && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[S] += 1;
		x++;
	}
	x = i;
	ret = id;

	//SO
	while (y >= 0 && x < _boardSize && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[SO] += 1;
		y--;
		x++;
	}
	x = i;
	y = j;
	ret = id;


	//O
	while (y >= 0 && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[O] += 1;
		y--;
	}
	y = j;
	ret = id;

	//NO
	while (y >= 0 && x >= 0 && ret == id) {
		ret = this->getCell(x, y);
		if (ret == id)
			count[NO] += 1;
		y--;
		x--;
	}

	if ((count[N] + count[S] - 1) >= 5 ||
	    (count[E] + count[O] - 1) >= 5 ||
	    (count[NO] + count[SE] - 1) >= 5 ||
	    (count[NE] + count[SO] - 1) >= 5)
		_winner = id;
	else
		_winner = 0;
}

int Board::getNbPieces() const
{
	int nb = 0;

	for (int x = 0; x < _boardSize; x++)
		for (int y = 0; y < _boardSize; y++)
			if (this->getCell(x, y) != CELL_EMPTY)
				nb++;

	return nb;
}

void Board::reset()
{
	if (!_board)
		this->createBoard();
	for (int x = 0; x < _boardSize; x++)
		for (int y = 0; y < _boardSize; y++)
			_board[x][y].setValue(CELL_EMPTY);
}

void Board::display() const
{
	int y;

	std::cout << "\n\n";
	this->printBorder();
	for (int x = 0; x < _boardSize; x++) {
		std::cout << "|";
		for (y = 0; y < _boardSize; y++)
			_board[x][y].display();
		std::cout << "|" << std::endl;

		        
	}
	this->printBorder();
	std::cout << "\n\n\n";
}

void Board::printBorder() const
{
	std::cout << "+";
	for (int x = 0; x < _boardSize; x++)
			std::cout << "-";
	std::cout << "+\n";
}

int Board::getCell(int x, int y) const
{
	int tmp;
	std::mutex lock;
	
	if (!(this->isValidCoord(x, y)))
		return OUT_OF_BOARD;
	lock.lock();
	tmp = _board[x][y].getValue();
	lock.unlock();
	return tmp;
}

int Board::getSize() const
{
	return _boardSize;
}

bool Board::isValidCoord(int x, int y) const
{
	return (x >= 0 && y >= 0 && x < _boardSize && y < _boardSize);
}

void Board::createBoard()
{
	_board = new Cell*[_boardSize];
	for (int i = 0; i < _boardSize; i++)
		_board[i] = new Cell[_boardSize];
}
