//
// EPITECH PROJECT, 2018
// maths
// File description:
// maths
//

#pragma once

#include <string>
#include <list>

#define MAX 1000000000

class Task
{
public:
	Task(std::string code, std::size_t duration, std::list<std::string> prerequis);
	~Task();
public:
	void link(std::string link);
	void setVisited();
	void setEarly(std::size_t time);
	void setLate(std::size_t time);
	void addPrerequis(std::string line);

	std::string getCode() const;
	std::size_t getDuration() const;
	std::size_t getEarly() const;
	std::size_t getLate() const;
	std::list<std::string> getPrerequis() const;
	std::list<std::string> getLink() const;
	bool getVisited() const;
	bool isLinkedWith(std::string task) const;
private:
	std::string _code;
	std::size_t _duration;
	std::size_t _early;
	std::size_t _late;
	std::list<std::string> _prerequis;
	std::list<std::string> _link;
	bool _visited;
};