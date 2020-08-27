//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// matrix.hpp
//

#pragma once

#include <vector>
#include <map>
#include "Account.hpp"

class Matrix
{
public:
	Matrix(std::map<std::string, Account *> accMap);
	~Matrix();
public:
	void floydWarshall();
	void createMatrix();
	void display(std::size_t n);
private:
	void createAdjacencyMatrix();
	void createLinkMatrix();
	void storeData();
private:
	std::map<std::string, Account *> _accMap;
	std::map<std::string, std::size_t> _nameToId;
	std::vector<std::string> _names;
	std::map<std::size_t, std::map<std::size_t, std::size_t> >_matrix;
	std::map<std::size_t, std::map<std::size_t, std::size_t> >_linkMatrix;
	std::size_t _nbFriends;
};
