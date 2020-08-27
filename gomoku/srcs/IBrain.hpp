//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// IBrain interface declaration
//

#pragma once

#include <vector>

class IBrain
{
public:
	virtual bool start(int size) = 0;
	virtual std::pair<int, int> turn(int x, int y) = 0;
	virtual std::pair<int, int> begin() = 0;
	virtual std::pair<int, int> board(std::vector<std::tuple<int, int, int>>) = 0;
	virtual bool end() = 0;
};