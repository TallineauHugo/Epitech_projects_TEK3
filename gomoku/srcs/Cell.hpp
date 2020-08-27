//
// EPITECH PROJECT, 2018
// gomoku
// File description:
// cell
//

#pragma once

class Cell
{
public:
	Cell();
	~Cell();
public:
	void display() const;
	void setValue(int val);	
	int getValue() const;	
private:
	int _value;
};
