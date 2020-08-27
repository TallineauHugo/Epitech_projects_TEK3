//
// EPITECH PROJECT, 2018
// morpion
// File description:
// AI
//

#include "AI.hpp"

#include <iostream>

AI::AI(int boardSize) : _size(boardSize), _winSize(3)
{
	for (int x = 0; x < _size; x++)
		for (int y = 0; y < _size; y++)
			_board[x][y] = 0;
}

AI::~AI()
{}

bool AI::putPiece(int x, int y, int id)
{
	if (_board[x][y] == 0 && x < _size && y < _size && x >= 0 && y >= 0) {
		_board[x][y] = id;
		return true;
	}
	return false;
}

char AI::disp(int value) const
{
	switch (value) {
	case 0:
		return ' ';
	case 1:
		return 'O';
	case 2:
		return 'X';
	default:
		return ' ';
		        
	}
}

void AI::displayBoard() const
{
	int y;

	std::cout << "\n\n\n";
	std::cout << "+ --> y\n";
	std::cout << "  +---+" << std::endl;
	for (int x = 0; x < _size; x++) {
		if (x < _size - 1)
			std::cout << "| |";
		else
			std::cout << "v |";
		for (y = 0; y < _size; y++)
			std::cout << disp(_board.at(x).at(y));
		std::cout << "|" << std::endl;
		        
	}
	std::cout << "x +---+" << std::endl;
	std::cout << "\n\n\n";
}

std::pair<int, int> AI::play(int depth)
{
	int max_val = LESS_INFINITE;
	int  val;
	std::pair<int, int> best_move;

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			if (_board[x][y] == 0) {
				_board[x][y] = 1;
				val = this->min(depth - 1);
				if (val > max_val || ((val == max_val) && (rand() % 2 == 0))) {
					max_val = val;
					best_move.first = x;
					best_move.second = y;
				}
				_board[x][y] = 0;
			}
		}
	}
	return best_move;
}

int AI::max(int depth)
{
	if (depth == 0 || winner() != 0)
		return eval();
	
	int max_val = LESS_INFINITE;
	int val;

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			if (_board[x][y] == 0) {
				_board[x][y] = 1;
				val = min(depth - 1);
				
				if (val > max_val || ((val == max_val) && (rand() % 2 == 0)))
					max_val = val;
				_board[x][y] = 0;
			}
		}
	}
	return max_val;
}

int AI::min(int depth)
{
	if (depth == 0 || winner() != 0)
		return eval();
	
	int min_val = INFINITE;
	int val;

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			if (_board[x][y] == 0) {
				_board[x][y] = 2;
				val = max(depth - 1);
					
				if (val < min_val)
					min_val = val;
				_board[x][y] = 0;
			}
		}
	}

	return min_val;
}

int AI::getNbPieces()
{
	int nb = 0;

	for (int x = 0; x < _size; x++)
		for (int y = 0; y < _size; y++)
			if (_board[x][y] != 0)
				nb++;
	return nb;
}

int AI::eval()
{
	int win;
	
	if ((win = winner()) != 0) {
		if (win == 1)
			return 1000 - getNbPieces();
		else if (win == 2)
			return -1000 + getNbPieces();
		else
			return 0;
	}
	return nbSeries(1, 2) - nbSeries(2, 2);
}

int AI::countDiagDesc(int id, int winSize)
{
	int nb = 0;
	int nbSeries = 0;
	
	for (int x = 0; x < _size; x++) {
		if (_board[x][x] == id) {
			nb++;
			if (nb == winSize)
				nbSeries++;
		}
		else
			nb = 0;
	}
	return nbSeries;
}

int AI::countDiagAsc(int id, int winSize)
{
	int nb = 0;
	int nbSeries = 0;
	
	for (int x = 0; x < _size; x++) {
		if (_board[x][_size - 1 - x] == id) {
			nb++;
			if (nb == winSize)
				nbSeries++;
		}
		else
			nb = 0;
	}
	return nbSeries;
}

int AI::countLine(int id, int winSize)
{
	int nb;
	int nbSeries = 0;

	for (int x = 0; x < _size; x++) {
		nb = 0;
		for (int y = 0; y < _size; y++) {
			if (_board[x][y] == id) {
				nb++;
				if (nb == winSize)
					nbSeries++;
			}
			else
				nb = 0;
		}
		nb = 0;
		for (int y = 0; y < _size; y++) {
			if (_board[y][x] == id) {
				nb++;
				if (nb == winSize)
					nbSeries++;
			}
			else
				nb = 0;
		}
	}
	return nbSeries;
}

int AI::nbSeries(int id, int winSize)
{
	int ret = countDiagDesc(id, winSize) + countDiagAsc(id, winSize) + countLine(id, winSize);

	return ret;
}

int AI::winner()
{
	int j1 = nbSeries(1, _winSize);
	int j2 = nbSeries(2, _winSize);

	if (j1)
		return 1;
	else if (j2)
		return 2;
	else
		if (getNbPieces() < 9)
			return 0;
	return 3;
}
