//
// EPITECH PROJECT, 2018
// maths
// File description:
// maths
//

#include "TaskManager.hpp"

int main(int ac, char **av)
{
	TaskManager task;

	if (ac != 2)
		return 84;
	return task.process(std::string(av[1]));
}
