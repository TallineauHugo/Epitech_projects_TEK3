//
// EPITECH PROJECT, 2018
// 303make
// File description:
// matrix
//

#include <iostream>

#include "Matrix.hpp"
#include "File.hpp"

Matrix::Matrix() : _size(0)
{}

Matrix::~Matrix()
{}

void Matrix::create(std::map<std::string, File*> mFiles)
{
	getFilesFromMap(mFiles);
	_size = _vFiles.size();
	for (std::size_t x = 0; x < _size; x++)
		for (std::size_t y = 0; y < _size; y++)
			_matrix[x][y] = _vFiles[y]->gotChild(_vFiles[x]);
}

void Matrix::display() const
{
	//display matrix tab
	for (std::size_t x = 0; x < _size; x++) {
		std::cout << "[";
		for (std::size_t y = 0; y < _size; y++) {
			std::cout << (((_matrix.at(x)).at(y)) ? "1" : "0") << ((y + 1 < _size) ? " " : "]\n");
		}
	}
	std::cout << std::endl;
}

void Matrix::getFilesFromMap(std::map<std::string, File*> map)
{
	std::map<std::string, File*>::iterator it = map.begin();

	while (it != map.end()) {
		_vFiles.push_back(it->second);
		it++;
	}
}

std::size_t Matrix::getSize() const
{
	return _size;
}
