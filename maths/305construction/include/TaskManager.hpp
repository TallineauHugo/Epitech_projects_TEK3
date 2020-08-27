//
// EPITECH PROJECT, 2018
// maths
// File description:
// maths
//

#pragma once

#include <string>
#include <map>
#include <vector>
#include "Task.hpp"

class TaskManager
{
public:
	TaskManager();
	~TaskManager();
public:
	int process(std::string filename);
private:
	bool loadTaskFromFile(std::string filename);
	bool processLine(std::string line);
	void fillEarlyGraph(Task *task);
	void fillLateGraph(Task *task);
	void buildGraph();
	std::vector<std::string> splitString(std::string line, char delim);
	std::list<std::string> findTasksForPrerequis(std::list<std::string> taskDone) const;
	std::list<Task*> getSortedListByEarly() const;
	void display() const;
private:
	std::map<std::string, Task*> _mTasks;
	std::list<std::string> _taskDone;
	Task *_start;
	Task *_end;
};