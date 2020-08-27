//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// hash
//

#include "Hash.hpp"
#include "Board.hpp"

#include <sstream>
#include <mutex>

Hash::Hash()
{}

Hash::~Hash()
{}

int Hash::getSituation(bool turn, std::string line) const
{
	std::mutex lock;
	int tmp;
	
	line = (turn ? "1" : "2") + line;
	lock.lock();
	if (_map.find(line) == _map.end())
		return HASH_ERROR;
	tmp = _map.at(line);
	lock.unlock();
	return tmp;
}

void Hash::storeSituation(bool turn, std::string line, int score)
{
	std::mutex lock;
	
	line = (turn ? "1" : "2") + line;
	lock.lock();
	if (_map.find(line) == _map.end())
		_map[line] = score;
	lock.unlock();
}
