//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// listener class implementation
//

#include <iostream>
#include <string>

#include "Listener.hpp"


Listener::Listener(IBrain *brain): _brain(brain)
{
	_methMap.insert(std::make_pair("START", &Listener::start));
	_methMap.insert(std::make_pair("TURN", &Listener::turn));
	_methMap.insert(std::make_pair("BEGIN", &Listener::begin));
	_methMap.insert(std::make_pair("BOARD", &Listener::board));
	_methMap.insert(std::make_pair("END", &Listener::end));
}

void Listener::run()
{
	char buff[2048];
	std::string command;
	std::string line;
	int ret = 84;

	fgets(buff, 2048, stdin);
	line = buff;
	do {
	    line = buff;
	    line.erase(line.find('\n'));
		command = line.substr(0, line.find(' '));
        if (line.find(' ') == std::string::npos)
            line = "";
		line.erase(0, line.find(' ') + 1);
		if (_methMap.find(command) != _methMap.end())
			ret = (this->*_methMap[command])(line);
		fgets(buff, 2048, stdin);
	} while (!ret);
}

int Listener::start(std::string str)
{
    int value = 20;

    if (!str.empty())
        value = std::stoi(str);
	if (!this->_brain->start(value)) {
		std::cout << "ERROR message - unsupported size or other error" << std::endl;
		return 84;
	}
	printf("OK\n");
	fflush(stdout);
	return 0;
}

int Listener::turn(std::string str)
{
	std::pair<int, int> pos;
	int x = std::stoi(str.substr(0, str.find(',')));
	int y = std::stoi(str.substr(str.find(',') + 1, std::string::npos));

	pos = this->_brain->turn(x, y);
	printf("%d,%d\n", pos.first, pos.second);
	fflush(stdout);
	return 0;
}

int Listener::begin(std::string ignored)
{
	std::pair<int, int> pos = this->_brain->begin();

	printf("%d,%d\n", pos.first, pos.second);
	fflush(stdout);
	return 0;
	(void)ignored;
}

int Listener::board(std::string str)
{
	std::cout << "Board <- " << str << std::endl;
	return 0;
}

int Listener::end(std::string ignored)
{
	this->_brain->end();
	return 0;
	(void)ignored;
}
