//
// EPITECH PROJECT, 2018
// 303make
// File description:
// file
//

#pragma once

#include <string>
#include <map>

class File
{
public:
	File(std::string filename);
	~File();
public:
	void setCompileCommand(std::string command);
	void addChild(File *file);
	
	void displayCommand(std::map<std::string, bool> &mCommands, bool printOwn) const;
	bool displayDependencies() const;
	std::string getName() const;
	bool gotChild(File *file) const;
private:
	std::string _filename;
	std::string _command;
	std::map<std::string, File*> _mChild;
};
