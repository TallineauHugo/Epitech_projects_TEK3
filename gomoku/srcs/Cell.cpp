//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// cell
//

#include <iostream>

#include "Cell.hpp"
#include "GomokuMacro.hpp"

Cell::Cell() : _value(CELL_EMPTY)
{}

Cell::~Cell()
{}

void Cell::display() const
{
	char c = ' ';
	
	switch (_value) {
	case 1:
		c = 'o';
		break;
	case 2:
		c = 'x';
		break;		
	}
	std::cout << c;
}

void Cell::setValue(int val)
{
	_value = val;
}

int Cell::getValue() const
{
	return _value;
}
