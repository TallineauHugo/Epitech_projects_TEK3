//
// EPITECH PROJECT, 2018
// 303make
// File description:
// parser
//

#pragma once

#define SPACE " "
#define EMPTY ""
#define TAB "\t"

#include <map>
#include <utility>
#include <fstream>

#include "Matrix.hpp"

class File;

class Parser
{
public:
	Parser();
	~Parser();
public:
	void parseFile(char *filename);
	void displayGraph() const;
	int displayDependencies(std::string filename) const;
private:
	std::ifstream &getNextBlock(std::ifstream &file,
				    std::pair<std::string, std::string> &block);
	std::ifstream &getNextLine(std::ifstream &file, std::string &buff,
				   char delim);
	void processBlock(std::pair<std::string, std::string> block);
	void createFile(const std::string filename);
	void epurestr(std::string &str);
	void replace(std::string &str, const std::string toReplace,
		     const std::string by, std::size_t len);
	void removeSpaces(std::string &str);
	void generateMatrix();
private:
	std::map<std::string, File*> _mFiles;
	Matrix _matrix;
};
