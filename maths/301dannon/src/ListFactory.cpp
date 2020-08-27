//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// list factory class implementation
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "ListFactory.hpp"

bool ListFactory::failed()
{
	return _failed;
}

std::vector<float> ListFactory::getListFromFile(char *filename)
{
	std::vector<float> list;
	std::ifstream file(filename);
	std::ifstream tmp(filename);
	std::stringstream buff;
	std::string valueStr;

	buff << tmp.rdbuf();
	if (buff.str().find_first_not_of("0123456789 .-") != std::string::npos) {
		std::cerr << "Values has to be numbers and must be seperated"
			" by spaces" << std::endl;
		this->_failed = true;
	}
	while (file >> valueStr)
		list.push_back(strtof(valueStr.c_str(), nullptr));
	return list;
}
