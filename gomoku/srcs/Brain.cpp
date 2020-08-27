//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// brain
//

#include <iostream>
#include <cstdlib>
#include <thread>
#include <algorithm>

#include "Brain.hpp"
#include "Board.hpp"
#include "GomokuMacro.hpp"

Brain::Brain(Board *board) : _winSize(STD_WINSIZE), _size(STD_BOARDSIZE), _board(board)
{
	_cut = std::make_tuple(-1, -1, -1);
}

Brain::~Brain()
{

}

void Brain::setSize(int size)
{
	_size = size;
}

std::pair<int, int> Brain::process(int depth)
{
	return this->bestMove(depth);
}

std::pair<int, int> Brain::bestMove(int depth)
{
    std::map<std::pair<int, int>, int> save;
    std::vector<std::pair<int, int>> saveRemaining;
	std::pair<int, int> bestMove;
	std::pair<int, int> check;
	int max_val = LESS_INFINITE;
	int val;

	_alpha = LESS_INFINITE;
	_beta = INFINITE;
	resetRemaining();
	while (getNextCheck(check)) {
	    save = _searchArea;
	    saveRemaining = _remaining;
		_board->setCell(check.first, check.second, OWN);
		addArea(check.first, check.second, OWN);
		val = this->min(depth - 1);
		if (val > max_val) {
			max_val = val;
			bestMove.first = check.first;
			bestMove.second = check.second;
		}
		_board->setCell(check.first, check.second, CELL_EMPTY);
        _searchArea = save;
        _remaining = saveRemaining;
	}
	return bestMove;
}

int Brain::min(int depth)
{
	int val = INFINITE;
	std::pair<int, int> check;
	std::map<std::pair<int, int>, int> save;
	std::vector<std::pair<int, int>> saveRemaining;

	if (!depth)// || _board->winner())
		return eval(false);

	if (std::get<2>(_cut) == depth) {
		int x2 = std::get<0>(_cut);
		int y2 = std::get<1>(_cut);
		if (_board->getCell(x2, y2) == CELL_EMPTY) {
			save = _searchArea;
			saveRemaining = _remaining;
			_board->setCell(x2, y2, FOE);
			addArea(check.first, check.second, FOE);
			val = std::min(val, max(depth - 1));

			if (val < _beta)
				_beta = val;
			_board->setCell(x2, y2, CELL_EMPTY);
			_searchArea = save;
			_remaining = saveRemaining;
			if (_alpha >= _beta) {
				_cut = std::make_tuple(x2, y2, depth);
				return val;
			}
		}
	}

	resetRemaining();
	while (getNextCheck(check)) {
		save = _searchArea;
		saveRemaining = _remaining;
		_board->setCell(check.first, check.second, FOE);
		addArea(check.first, check.second, FOE);
		val = std::min(val, max(depth - 1));

		if (val < _beta)
			_beta = val;
		_board->setCell(check.first, check.second, CELL_EMPTY);
		if (_alpha >= _beta)
			break;
		_board->setCell(check.first, check.second, CELL_EMPTY);
		_searchArea = save;
		_remaining = saveRemaining;
	}

	return val;
}

int Brain::max(int depth)
{
	int val = LESS_INFINITE;
    std::pair<int, int> check;
    std::map<std::pair<int, int>, int> save;
    std::vector<std::pair<int, int>> saveRemaining;

    if (!depth)// || _board->winner())
		return eval(true);

	if (std::get<2>(_cut) == depth) {
		int x2 = std::get<0>(_cut);
		int y2 = std::get<1>(_cut);
		if (_board->getCell(x2, y2) == CELL_EMPTY) {
            save = _searchArea;
            saveRemaining = _remaining;
			_board->setCell(x2, y2, OWN);
            addArea(check.first, check.second, OWN);
			val = std::max(val, min(depth - 1));

			if (val > _alpha)
				_alpha = val;
			_board->setCell(x2, y2, CELL_EMPTY);
            _searchArea = save;
            _remaining = saveRemaining;
			if (_alpha >= _beta) {
				_cut = std::make_tuple(x2, y2, depth);
				return val;
			}
		}
	}
    resetRemaining();
    while (getNextCheck(check)) {
        save = _searchArea;
        saveRemaining = _remaining;
        _board->setCell(check.first, check.second, OWN);
        addArea(check.first, check.second, OWN);
        val = std::min(val, max(depth - 1));

        if (val < _beta)
            _beta = val;
		_searchArea = save;
		_remaining = saveRemaining;
        _board->setCell(check.first, check.second, CELL_EMPTY);
        if (_alpha >= _beta)
            break;
        _board->setCell(check.first, check.second, CELL_EMPTY);
    }

	return val;
}

int Brain::getNbPieces() const
{
	return _board->getNbPieces();
}

int Brain::eval(bool turn)
{
//	int win;
	int score;

//	win = _board->winner();
//	if (win != 0) {
//		if (win == 1)
//			return WIN_SCORE - getNbPieces();
//		else if (win == 2)
//			return -WIN_SCORE + getNbPieces();
//		else
//			return 0;
//	}

	int scoreFoe = analyzeBoard(FOE, turn);
	int scoreOwn = analyzeBoard(OWN, turn);

//	std::cout << "foe: " << scoreFoe << " | own: " << scoreOwn << std::endl << std::endl;
//	score = (turn ? scoreOwn - scoreFoe : scoreFoe - scoreOwn);
	score = scoreOwn - scoreFoe;
	return score;
}

int Brain::analyzeBoard(int playerID, bool turn)
{
	std::vector<std::thread> threads;

	threads.emplace_back(&Brain::analyzeHorizontal, this, playerID, turn);
	threads.emplace_back(&Brain::analyzeVertical, this, playerID, turn);
	threads.emplace_back(&Brain::analyzeDiagTB, this, playerID, turn);
//	threads.emplace_back(&Brain::analyzeDiagBT, this, playerID, turn);
	analyzeDiagBT(playerID, turn);

	threads[0].join();
	threads[1].join();
	threads[2].join();
//	threads[3].join();

	return _retHorizontal + _retVertical + _retDiagTB + _retDiagBT;
/*	return analyzeHorizontal(playerID, turn)
		+ analyzeVertical(playerID, turn)
		+ analyzeDiagTB(playerID, turn)
		+ analyzeDiagBT(playerID, turn);*/
}

void Brain::analyzeHorizontal(int id, bool turn)
{
	int score = 0;
	int count = 0;
	int openEnds = 0;
	int cell;
	int size;
	int vSize;
	std::vector<std::string> vLine;
	std::string line = "";

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++)
			line += _board->getCell(x, y);
		vLine.push_back(line);
		line = "";
	}
	vSize = vLine.size();

	for (int b = 0; b < vSize; b++) {
		line = vLine[b];
		size = line.size();
		count = 0;
		openEnds = 0;
		for (int i = 0; i < size; i++) {
			cell = line[i];
			if (cell == id)
				count++;
			else if (cell == CELL_EMPTY && count > 0) {
				openEnds++;
				score += computeScore(count, openEnds, (((id == 1) == turn)));
				count = 0;
				openEnds = 1;
			}
			else if (cell == CELL_EMPTY)
				openEnds = 1;
			else if (count > 0) {
				score += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 0;
			}
			else
				openEnds = 0;
		}
		if (count > 0)
			score += computeScore(count, openEnds, ((id == 1) == turn));
	}
	_retHorizontal = score;
}

void Brain::analyzeVertical(int id, bool turn)
{
	int score = 0;
	int count = 0;
	int openEnds = 0;
	int cell = 0;
	int size = 0;
	std::string line = "";
	int vSize = 0;
	std::vector<std::string> vLine;

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++)
			line += _board->getCell(y, x);
		vLine.push_back(line);
		line = "";
	}
	vSize = vLine.size();
	for (int b = 0; b < vSize; b++) {
		line = vLine[b];
		size = line.size();
		count = 0;
		openEnds = 0;
		for (int i = 0; i < size; i++) {
			cell = line[i];
			if (cell == id)
				count++;
			else if (cell == CELL_EMPTY && count > 0) {
				openEnds++;
				score += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 1;
			}
			else if (cell == CELL_EMPTY)
				openEnds = 1;
			else if (count > 0) {
				score += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 0;
			}
			else
				openEnds = 0;
		}
		if (count > 0)
			score += computeScore(count, openEnds, ((id == 1) == turn));
	}
	_retVertical = score;
}

void Brain::analyzeDiagTB(int id, bool turn)
{
	int score1 = 0;
	int score2 = 0;
	int count = 0;
	int openEnds = 0;
	int cell;
	int size;
	std::string line = "";
	int vSize = 0;
	std::vector<std::string> vLine;

	for (int x = 0; x <= _size - _winSize; x++) {
		for (int y = 0; y < _size; y++)
			line += _board->getCell(y + x, y);
		vLine.push_back(line);
		line = "";
	}
	vSize = vLine.size();
	for (int b = 0; b < vSize; b++) {
		line = vLine[b];
		size = line.size();
		count = 0;
		openEnds = 0;
		for (int i = 0; i < size; i++) {
			cell = line[i];
			if (cell == id)
				count++;
			else if (cell == CELL_EMPTY && count > 0) {
				openEnds++;
				score1 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 1;
			}
			else if (cell == CELL_EMPTY)
				openEnds = 1;
			else if (count > 0) {
				score1 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 0;
			}
			else
				openEnds = 0;
		}
		if (count > 0)
			score1 += computeScore(count, openEnds, ((id == 1) == turn));
	}
	count = 0;
	openEnds = 0;
	line = "";
	vLine.clear();

	for (int w = 0; w <= _size - _winSize; w++) {
		for (int z = 0; z < _size; z++)
			line += _board->getCell(z, z + w);
		vLine.push_back(line);
		line = "";
	}
	vSize = vLine.size();
	for (int c = 0; c < vSize; c++) {
		line = vLine[c];
		size = line.size();
		count = 0;
		openEnds = 0;
		for (int a = 0; a < size; a++) {

			cell = line[a];
			if (cell == id)
				count++;
			else if (cell == CELL_EMPTY && count > 0) {
				openEnds++;
				score2 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 1;
			}
			else if (cell == CELL_EMPTY)
				openEnds = 1;
			else if (count > 0) {
				score2 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 0;
			}
			else
				openEnds = 0;
		}
		if (count > 0)
			score2 += computeScore(count, openEnds, ((id == 1) == turn));
	}
	_retDiagTB = score1 + score2;
}

void Brain::analyzeDiagBT(int id, bool turn)
{

	int score1 = 0;
	int score2 = 0;
	int count = 0;
	int openEnds = 0;
	int cell;
	int size;
	std::string line = "";
	int vSize = 0;
	std::vector<std::string> vLine;

	for (int x = 0; x <= _size - _winSize; x++) {
		for (int y = 0; y < _size; y++)
			line += _board->getCell(_size - 1 - y - x, y);
		vLine.push_back(line);
		line = "";
	}
	vSize = vLine.size();
	for (int b = 0; b < vSize; b++) {
		line = vLine[b];
		size = line.size();
		count = 0;
		openEnds = 0;
		for (int i = 0; i < size; i++) {
			cell = line[i];
			if (cell == id)
				count++;
			else if (cell == CELL_EMPTY && count > 0) {
				openEnds++;
				score1 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 1;
			}
			else if (cell == CELL_EMPTY)
				openEnds = 1;
			else if (count > 0) {
				score1 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 0;
			}
			else
				openEnds = 0;
		}
		if (count > 0)
			score1 += computeScore(count, openEnds, ((id == 1) == turn));
	}
	count = 0;
	openEnds = 0;
	line = "";
	vLine.clear();

	for (int w = 0; w <= _size - _winSize; w++) {
		for (int z = 0; z < _size; z++)
			line += _board->getCell(_size - 1 - z, z + w);
		vLine.push_back(line);
		line = "";
	}
	vSize = vLine.size();
	for (int c = 0; c < vSize; c++) {
		line = vLine[c];
		size = line.size();
		count = 0;
		openEnds = 0;
		for (int a = 0; a < size; a++) {

			cell = line[a];
			if (cell == id)
				count++;
			else if (cell == CELL_EMPTY && count > 0) {
				openEnds++;
				score2 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 1;
			}
			else if (cell == CELL_EMPTY)
				openEnds = 1;
			else if (count > 0) {
				score2 += computeScore(count, openEnds, ((id == 1) == turn));
				count = 0;
				openEnds = 0;
			}
			else
				openEnds = 0;
		}
		if (count > 0)
			score2 += computeScore(count, openEnds, ((id == 1) == turn));
	}
	_retDiagBT = score1 + score2;
}

int Brain::computeScore(int count, int ends, bool turn) const
{
	if (ends == 0 && count < 5)
		return 0;
	switch (count) {
	case 4:
		return (ends == 1) ?
			(turn ? WIN_SCORE / 2 : 50) :
			(turn ? WIN_SCORE / 2 + 50000 : 500000);
	case 3:
		return (ends == 1) ? (turn ? 20 : 15) : (turn ? 10000 : 50);
	case 2:
		return (ends == 1) ? 7 : 10;
	case 1:
		return (ends == 1) ? 1 : 2;
	default:
		return WIN_SCORE;
	}
}

void Brain::addArea(int posX, int posY, int player)
{
	std::pair<int, int> npos;
	int nPosX;
	int nPosY;
	int x;
	int y;

	npos = std::make_pair(posX, posY);
	if (_searchArea.find(npos) != _searchArea.end())
	    _searchArea.erase(npos);
	for (x = -3; x <= 3; x++) {
		for (y = -3; y <= 3; y++) {
			nPosX = posX + x;
			nPosY = posY + y;
			if (abs(x) + abs(y) <= 3 && _board->getCell(nPosX, nPosY) == CELL_EMPTY) {
			    npos.first = posX + x;
			    npos.second = posY + y;
				if (_searchArea.find(npos) == _searchArea.end()) {
					_searchArea[npos] = player;
                    _remaining.push_back(npos);
				}
			}
		}
	}
}

void Brain::resetRemaining()
{
    std::map<std::pair<int, int>, int>::iterator it = _searchArea.begin();

    _remaining.clear();
    while (it != _searchArea.end()) {
        _remaining.push_back(std::make_pair(it->first.first, it->first.second));
        it++;
    }
}

bool Brain::getNextCheck(std::pair<int, int> &check)
{
    if (_remaining.empty())
        return false;
    check = _remaining.at(0);
    _remaining.erase(_remaining.begin());
    return true;
}

void Brain::end()
{
	_searchArea.clear();
	_remaining.clear();
}
