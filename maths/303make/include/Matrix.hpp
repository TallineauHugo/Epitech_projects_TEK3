//
// EPITECH PROJECT, 2018
// 303make
// File description:
// Matrix
//

#pragma once

#include <map>
#include <vector>
#include <string>

class File;

class Matrix
{
public:
	Matrix();
	~Matrix();
public:
	void create(std::map<std::string, File*> mFiles);
	void display() const;
	std::size_t getSize() const;
private:
	void getFilesFromMap(std::map<std::string, File*> map);
private:
	std::map<std::size_t, std::map<std::size_t, bool> > _matrix;
	std::vector<File*> _vFiles;
	std::size_t _size;
};
