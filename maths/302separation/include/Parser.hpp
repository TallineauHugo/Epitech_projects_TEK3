//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// parser.hpp
//

#pragma once

#include <string>
#include "Matrix.hpp"

class Parser
{
public:
	Parser();
	~Parser();
public:
	void parseFile(char *filename);
	void displayFull(int n);
	void displayLinkBetween(std::string acc1, std::string acc2);
private:
	std::ifstream &getNextLine(std::ifstream &file, std::string &buff, char delim);
	void processLine(std::string s);
	void sort();
	void buildAdjacencyMatrix();
private:
	std::map<std::string, Account *> _accountMap;
        Matrix *_adjacencyMatrix;
	Matrix *_linkMatrix;
};
