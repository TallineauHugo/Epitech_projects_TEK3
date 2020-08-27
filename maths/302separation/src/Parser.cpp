//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// parser.cpp
//

#include <iostream>
#include <fstream>
#include "Parser.hpp"

Parser::Parser()
{
	
}

Parser::~Parser()
{
	std::map<std::string, Account *>::iterator it = _accountMap.begin();

	while (it != _accountMap.end()) {
		delete _accountMap[it->first];
		it++;
	}
}

void Parser::sort()
{
	// trier la liste par odre alphabetique
}

std::ifstream &Parser::getNextLine(std::ifstream &file, std::string &buff, char delim)
{
	buff = "";
	while (file && (buff == "" || buff == "\n")) {
		getline(file, buff, delim);
//		epurestr(buff);
	}
	return file;
}

void Parser::processLine(std::string s)
{
	std::string acc1;
	std::string acc2;
	std::string delim(" is friends with ");
	std::size_t pos = s.find(delim, 0);

	if (pos == std::string::npos)
		exit(84);
	acc1 = s.substr(0, pos);
	acc2 = s.substr(pos + delim.size(), std::string::npos);
	if (_accountMap.find(acc1) == _accountMap.end())
		_accountMap[acc1] = new Account(acc1);
	if (_accountMap.find(acc2) == _accountMap.end())
		_accountMap[acc2] = new Account(acc2);
	_accountMap[acc1]->addFriend(acc2, _accountMap[acc2]);
	_accountMap[acc2]->addFriend(acc1, _accountMap[acc1]);
}

void Parser::parseFile(char *filename)
{
	std::ifstream file(filename);
	std::string s;

	if (!file.is_open())
		exit(84);
	while (getNextLine(file, s, '\n')) {
		processLine(s);
	}
	sort();
	buildAdjacencyMatrix();
}

void Parser::buildAdjacencyMatrix()
{
	_adjacencyMatrix = new Matrix(_accountMap);

	_adjacencyMatrix->createMatrix();
}

void Parser::displayFull(int n)
{
	if (n >= 0)
		_adjacencyMatrix->display((std::size_t)n);
	delete _adjacencyMatrix;
}

void Parser::displayLinkBetween(std::string acc1, std::string acc2)
{       
	std::cout << "degree of separation between " << acc1 << " and " << acc2;
	std::cout << ": ";
	if (_accountMap.find(acc1) == _accountMap.end() || _accountMap.find(acc2) == _accountMap.end())
		std::cout << "-1" << std::endl;
	else
		std::cout << (acc1 == acc2 ? 0 : _accountMap[acc1]->distFrom(acc2)) << std::endl;
	delete _adjacencyMatrix;
}
