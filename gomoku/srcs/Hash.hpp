//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// hash
//

#pragma once

#include <map>
#define HASH_ERROR -666

class Board;

class Hash
{
public:
	Hash();
	~Hash();
public:
	int getSituation(bool turn, std::string line) const;
	void storeSituation(bool turn, std::string line, int score);
private:
	std::map<std::string, int> _map;
};
