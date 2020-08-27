//
// EPITECH PROJECT, 2018
// maths
// File description:
// maths
//

#include <algorithm>
#include "Task.hpp"

bool Task::isLinkedWith(std::string task) const
{
	return (std::find(_link.begin(), _link.end(), task) != _link.end());
}

bool Task::getVisited() const
{
	return _visited;
}

void Task::setVisited()
{
	_visited = true;
}

void Task::link(std::string link)
{
	_link.push_back(link);
}

void Task::setEarly(std::size_t time)
{
	_early = time;
}

void Task::setLate(std::size_t time)
{
	_late = time;
}

void Task::addPrerequis(std::string line)
{
	_prerequis.push_back(line);
}

std::string Task::getCode() const
{
	return _code;
}

std::size_t Task::getDuration() const
{
	return _duration;
}

std::size_t Task::getEarly() const
{
	return _early;
}

std::size_t Task::getLate() const
{
	return _late;
}

std::list<std::string> Task::getPrerequis() const
{
	return _prerequis;
}

std::list<std::string> Task::getLink() const
{
	return _link;
}

Task::Task(std::string code, std::size_t duration, std::list<std::string> prerequis)
	: _code(code), _duration(duration), _early(0), _late(99999999), _prerequis(prerequis), _visited(false)
{

}

Task::~Task()
{}
