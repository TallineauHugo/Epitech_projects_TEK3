//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// brain
//

#pragma once

#include <tuple>
#include <utility>

#include <vector>

#include "Hash.hpp"

class Board;


#define LESS_INFINITE -2000000000
#define INFINITE 2000000000
#define STD_WINSIZE 5
#define STD_BOARDSIZE 20

class Brain
{
public:
	Brain(Board *board);
	~Brain();
public:
	void setSize(int size);
	std::pair<int, int> process(int depth);

    void addArea(int posX, int posY, int player);
    void resetRemaining();
    bool getNextCheck(std::pair<int, int> &check);
    void end();
private:
	std::pair<int, int> bestMove(int depth);
	int min(int depth);
	int max(int depth);
	int getNbPieces() const;
	int eval(bool p1);
	int analyzeBoard(int playerID, bool turn);
	void analyzeHorizontal(int id, bool turn);
	void analyzeVertical(int id, bool turn);
	void analyzeDiagTB(int id, bool turn);
	void analyzeDiagBT(int id, bool turn);
	int computeScore(int count, int openEnds, bool turn) const;

private:
	std::map<std::pair<int, int>, int> _searchArea;
	std::vector<std::pair<int, int>> _remaining;

	int _winSize;
	int _size;	
	Board *_board;
	int _alpha;
	int _beta;
	std::tuple<int, int, int> _cut;
//	Hash _hash;

	int _retHorizontal;
	int _retVertical;
	int _retDiagTB;
	int _retDiagBT;
};
