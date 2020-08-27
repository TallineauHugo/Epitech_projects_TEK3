//
// EPITECH PROJECT, 2018
// 303make
// File description:
// file
//

#include <iostream>

#include "File.hpp"

File::File(std::string filename) : _filename(filename)
{}

File::~File()
{}

bool File::displayDependencies() const
{
	std::map<std::string, File*>::const_iterator it = _mChild.begin();

	if (it == _mChild.end())
		return false;
	while (it != _mChild.end()) {
		std::cout << _filename << " -> ";
		if ((it->second)->displayDependencies() == false)
			std::cout << it->first << std::endl;
		it++;
	}
	return true;
}

void File::displayCommand(std::map<std::string, bool> &mCommands, bool printOwn) const
{
	std::map<std::string, File*>::const_iterator it = _mChild.begin();
	std::string tmp;

	if (!_command.empty() && printOwn == true) {
		tmp = _command + "\n";
		mCommands[tmp] = true;
	}

	while (it != _mChild.end()) {
		(it->second)->displayCommand(mCommands, true);
		it++;
	}
}

void File::setCompileCommand(std::string command)
{
	_command = command;
}

void File::addChild(File *file)
{
	_mChild[file->getName()] = file;
}

std::string File::getName() const
{
	return _filename;
}

bool File::gotChild(File *file) const
{
	return (_mChild.find(file->getName()) != _mChild.end());
}
