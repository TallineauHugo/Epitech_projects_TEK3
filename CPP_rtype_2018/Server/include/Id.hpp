//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// id
//

#pragma once

#include <string>

class Id
{
public:
	static Id *getInstance() {
		static Id instance;

		return &instance;
	}
	~Id();

	std::size_t getNextId();
private:
	Id();
	std::size_t _id;
};