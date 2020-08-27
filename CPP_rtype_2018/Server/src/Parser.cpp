//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// parser
//

#include <fstream>
#include <sstream>
#include "Parser.hpp"

Parser::Parser()
{}

Parser::~Parser()
{}

std::vector<std::string> Parser::splitStringToVector(std::string file, char delim)
{
	std::vector<std::string> vTokens;
	std::string token;
	std::istringstream tokenStream(file);

	while (std::getline(tokenStream, token, delim))
		vTokens.push_back(token);

	return vTokens;
}

std::pair<std::string, std::string> Parser::splitStringToPair(std::string line, char delim)
{
	std::pair<std::string, std::string> stat;
	std::size_t pos = line.find(delim);
	
	stat.first = line.substr(0, pos);
	stat.second = line.substr(pos + 1, std::string::npos);
	
	return stat;
}

bool Parser::readFileByName(std::string name, std::string &content)
{
	std::string filepath = name;
	std::ifstream file(filepath);

	if (file.is_open() == false)
		return false;
	
	std::string str((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	content = str;
	
	return true;
}