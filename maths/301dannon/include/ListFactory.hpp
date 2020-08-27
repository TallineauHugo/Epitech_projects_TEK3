//
// EPITECH PROJECT, 2018
// 301dannon
// File description:
// list factory class declaration
//

#pragma once

#include <vector>
#include <string>

class ListFactory
{
public:
	ListFactory() = default;
	~ListFactory() = default;

	std::vector<float> getListFromFile(char *filename);
	bool failed();
private:
	bool _failed = false;
};