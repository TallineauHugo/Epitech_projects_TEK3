//
// EPITECH PROJECT, 2018
// morpion
// File description:
// AI
//

#pragma once

#include <map>

#define LESS_INFINITE -9999
#define INFINITE 9999

class AI
{
public:
	AI(int boardSize);
	~AI();
public:
	std::pair<int, int> play(int depth);
	int max(int depth);
	int min(int depth);
	int eval();
	int winner();
	bool putPiece(int x, int y, int id);
	void displayBoard() const;
private:
	int getNbPieces();
	int nbSeries(int id, int winSize);
	int countLine(int id, int winSize);
	int countDiagDesc(int id, int winSize);
	int countDiagAsc(int id, int winSize);
	char disp(int value) const;
	
private:
	int _size;
	int _winSize;
	std::map<int, std::map<int, int>> _board;
};
