//
// EPITECH PROJECT, 2018
// 303make
// File description:
// parser
//

#include <iostream>

#include "Parser.hpp"
#include "File.hpp"

Parser::Parser()
{}

Parser::~Parser()
{}

void Parser::parseFile(char *filename)
{
	std::ifstream file(filename);
	std::pair<std::string, std::string> block;

	if (!file.is_open())
		exit(84);
	while (getNextBlock(file, block)) {
		processBlock(block);
	}
	this->generateMatrix();
}

void Parser::generateMatrix()
{
	_matrix.create(_mFiles);
}

void Parser::displayGraph() const
{
	std::map<std::string, File*>::const_iterator it;
	
	_matrix.display();
	
	it = _mFiles.begin();
	while (it != _mFiles.end()) {
		(it->second)->displayDependencies();
		it++;
	}
}

int Parser::displayDependencies(std::string filename) const
{
	std::map<std::string, bool> mCommands;
	std::map<std::string, bool>::const_iterator it;
	
	if (_mFiles.find(filename) == _mFiles.end())
		return 84;
	(_mFiles.at(filename))->displayCommand(mCommands, false);
	it = mCommands.begin();
	while (it != mCommands.end()) {
		std::cout << it->first;
		it++;
	}
	return 0;
}

std::ifstream &Parser::getNextBlock(std::ifstream &file,
			  std::pair<std::string, std::string> &block)
{
	std::string s;
	
	if (!getNextLine(file, s, '\n'))
		return file;
	if (s.find_first_of(':') == std::string::npos)
		exit(84);
	//check le format tty: tty.o fc.o
	block.first = s;

	if (!getNextLine(file, s, '\n'))
		return file;
	//check le format cc -o tty tty.o fc.o
	block.second = s;

	return file;
}

std::ifstream &Parser::getNextLine(std::ifstream &file, std::string &buff, char delim)
{
	buff = "";
	while (file && (buff == "" || buff == "\n")) {
		getline(file, buff, delim);
		epurestr(buff);
	}
	return file;
}

void Parser::processBlock(std::pair<std::string, std::string> block)
{
	std::string low;
	std::string high;
	std::size_t from = 0;
	std::size_t to = 0;

	//get first elements before the ':'
	to = (block.first).find_first_of(':');
	low = (block.first).substr(0, to);
	(block.first).erase(0, to + 1);
	
	//create associated file and assign compile command
	this->createFile(low);
	_mFiles[low]->setCompileCommand(block.second);

	//get linked elements
	while ((from = (block.first).find_first_not_of(' ')) != std::string::npos) {
		to = (block.first).find_first_of(' ', from);
		high = (block.first).substr(from, to - 1);
		(block.first).erase(from, to);
		
		//create associated file and assign childrens
		this->createFile(high);
		_mFiles[high]->addChild(_mFiles[low]);
	}
}

void Parser::createFile(const std::string filename)
{
	if (_mFiles.find(filename) == _mFiles.end())
		_mFiles[filename] = new File(filename);
}

void Parser::removeSpaces(std::string &str)
{
	size_t index = 0;

	index = str.find("  ", index);
	while (index != std::string::npos) {
		str.replace(index, 2, SPACE);
		index = str.find("  ", 0);
		        
	}
	if (str == EMPTY)
		return;
	index = str.find(SPACE, 0);
	if (index == 0)
		str.replace(index, 1, EMPTY);
//	index = str.find_last_of(SPACE);
//	if (index == (str.size() - 1))
//		str.replace(index, 1, EMPTY);
}

void Parser::replace(std::string &str, const std::string toReplace,
			   const std::string by, size_t len)
{
	size_t index = 0;

	while (1) {
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, len, by);
	}
}

void Parser::epurestr(std::string &str)
{
	this->replace(str, TAB, SPACE, 1);
//	this->replace(str, "\n", EMPTY, 1);
	this->removeSpaces(str);
}
