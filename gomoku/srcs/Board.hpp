//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// board
//

#pragma once

#define N 0
#define NE 1
#define E 2
#define SE 3
#define S 4
#define SO 5
#define O 6
#define NO 7

class Cell;

class Board
{
public:
	Board();
	~Board();
public:
	bool setSize(int boardSize);
	bool setCell(int x, int y, int value);
	int winner() const;
	int getNbPieces() const;
	void reset();
	void display() const;
        int getCell(int x, int y) const;
	int getSize() const;
private:
	void createBoard();
	void checkWin(int x, int y, int id);
	bool isValidCoord(int x, int y) const;

	void printBorder() const;
private:
	int _boardSize;
	int _winner;
	Cell **_board;
};
