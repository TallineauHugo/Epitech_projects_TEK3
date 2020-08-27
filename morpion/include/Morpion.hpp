//
// EPITECH PROJECT, 2018
// morpion
// File description:
// morpion
//

#pragma once

#include <map>

class AI;

class Morpion
{
public:
	Morpion(int boardSize);
	~Morpion();
public:
	void start();
private:
	void resetBoard();
private:
	int _size;
	AI *ai;
};
