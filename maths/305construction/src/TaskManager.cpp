//
// EPITECH PROJECT, 2018
// maths
// File description:
// maths
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <algorithm>
#include "TaskManager.hpp"

int TaskManager::process(std::string filename)
{
	bool ret = this->loadTaskFromFile(filename);
	if (ret)
		this->display();
	return (ret) ? 0 : 84;
}

bool TaskManager::loadTaskFromFile(std::string filename)
{
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file.good())
		return false;
	while (std::getline(file, line)) {
		if (!this->processLine(line))
			return false;
	}
	this->buildGraph();
	return true;
}

void TaskManager::fillLateGraph(Task *task)
{
	std::list<std::string> prerequis = task->getPrerequis();
	std::list<std::string>::iterator it;

	it = prerequis.begin();
	while (it != prerequis.end()) {
		if (_mTasks.find(*it) != _mTasks.end() &&
		    _mTasks[*it]->getLate() > task->getLate() - _mTasks[*it]->getDuration())
			_mTasks[*it]->setLate(task->getLate() -
							    _mTasks[*it]->getDuration());
		this->fillLateGraph(_mTasks[*it]);
		it++;
	}
}

void TaskManager::fillEarlyGraph(Task *task)
{
	std::list<std::string> link = task->getLink();
	std::list<std::string>::iterator it = link.begin();
	std::size_t amount;

	amount = task->getEarly() + task->getDuration();
	while (it != link.end()) {
		if (_mTasks[*it]->getEarly() < amount)
			_mTasks[*it]->setEarly(amount);
		this->fillEarlyGraph(_mTasks[*it]);
		it++;
	}
}

void TaskManager::buildGraph()
{
	std::map<std::string, Task*>::iterator tasks = _mTasks.begin();
	std::list<std::string> prerequis;
	std::list<std::string>::iterator it;

	_start = new Task("BEGIN", 0, prerequis);
	_end = new Task("END", 0, prerequis);

	while (tasks != _mTasks.end()) {
		prerequis = tasks->second->getPrerequis();
		if (prerequis.empty())
			_start->link(tasks->first);
		else {
			it = prerequis.begin();
			while (it != prerequis.end()) {
				if (tasks->second->isLinkedWith(*it))
					exit(84);
				if (_mTasks.find(*it) != _mTasks.end())
					_mTasks[*it]->link(tasks->first);
				it++;
			}
		}
		tasks++;
	}
	_mTasks[_end->getCode()] = _end;
	tasks = _mTasks.begin();
	while (tasks != _mTasks.end()) {
		if (tasks->second->getLink().empty() && tasks->second->getCode() != _end->getCode()) {
			tasks->second->link(_end->getCode());
			_mTasks[_end->getCode()]->addPrerequis(tasks->first);
		}
		tasks++;
	}
	this->fillEarlyGraph(_start);
	_mTasks[_end->getCode()]->setLate(_end->getEarly());
	this->fillLateGraph(_end);
}

bool TaskManager::processLine(std::string line)
{
	std::vector<std::string> vTokens = this->splitString(line, ';');
	std::list<std::string> prerequis;
	std::size_t size = vTokens.size();

	if (size < 3 || vTokens[2].find_first_not_of("0123456789") != std::string::npos)
		return false;
	for (std::size_t i = 3; i < size; i++)
		prerequis.push_back(vTokens[i]);
	_mTasks[vTokens[0]] = new Task(vTokens[0], std::stoi(vTokens[2]), prerequis);

	return true;
}

std::vector<std::string> TaskManager::splitString(std::string line, char delim)
{
        std::vector<std::string> vTokens;
        std::string token;
        std::istringstream tokenStream(line);

        while (std::getline(tokenStream, token, delim))
                vTokens.push_back(token);

        return vTokens;
}

std::list<Task*> TaskManager::getSortedListByEarly() const
{
	std::map<std::string, Task*> tasks = _mTasks;
	std::map<std::string, Task*>::const_iterator mit = tasks.begin();
	std::list<Task*> list;
	std::list<Task*>::iterator it;
	std::list<Task*> ret;
	std::list<Task*>::iterator tmp;
	std::pair<std::size_t, std::size_t> max = std::make_pair(0, 0);

	while (mit != tasks.end()) {
		if (mit->second->getCode() != _end->getCode())
			list.push_back(mit->second);
		mit++;
	}

	while (!list.empty()) {
		it = list.begin();
		while (it != list.end()) {
			if ((*it)->getEarly() > max.first || ((*it)->getEarly() >= max.first && (*it)->getDuration() >= max.second)) {
				max = std::make_pair((*it)->getEarly(), (*it)->getDuration());
				tmp = it;
			}
			it++;
		}
		ret.push_front(*tmp);
		list.erase(tmp);
		max = std::make_pair(0, 0);
	}
	return ret;
}

void TaskManager::display() const
{
	std::list<Task*> sortedList = this->getSortedListByEarly();
	std::list<Task*>::iterator it = sortedList.begin();
	std::size_t i = 0;
	std::size_t aim;

	std::cout << "Total duration of construction: " << _end->getEarly() << " weeks" << std::endl << std::endl;

	while (it != sortedList.end()) {
		std::cout << (*it)->getCode() << " must begin ";
		if ((*it)->getEarly() == (*it)->getLate())
			std::cout << "at t=" << (*it)->getEarly() << std::endl;
		else
			std::cout << "between t=" << (*it)->getEarly() << " and t=" << (*it)->getLate() << std::endl;
		it++;
	}
	std::cout << std::endl;

	it = sortedList.begin();
	while (it != sortedList.end()) {
		std::cout << (*it)->getCode() << "\t(" << (*it)->getLate() - (*it)->getEarly() << ")\t";
		aim = (*it)->getEarly();
		while (i < aim) {
			std::cout << " ";
			i++;
		}
		aim = (*it)->getEarly() + (*it)->getDuration();
		while (i < aim) {
			std::cout << "=";
			i++;
		}
		std::cout << std::endl;
		i = 0;
		it++;
	}
}

TaskManager::TaskManager()
{}

TaskManager::~TaskManager()
{}
