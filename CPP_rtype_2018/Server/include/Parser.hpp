//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// parser
//

#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>

class Parser
{
public:
	static Parser *getInstance() {
		static Parser instance;

		return &instance;
	}
	~Parser();
public:
	std::vector<std::string> splitStringToVector(std::string file, char delim);
	std::pair<std::string, std::string> splitStringToPair(std::string line, char delim);
	bool readFileByName(std::string name, std::string &file);
private:
	Parser();
};