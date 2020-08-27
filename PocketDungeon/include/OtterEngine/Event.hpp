#pragma once

#include <stdlib.h>
#include <vector>
#include "OtterEngine.hpp"

template <class T> class OtterEngine::Event
{
public:
	Event(std::string name, int (T:: *function)(OtterEngine::Engine *oe), bool (T:: *condition)(OtterEngine::Engine *oe), int priority = 0);
	~Event();
	
	bool verification(OtterEngine::Engine *oe, T &obj);
	int reaction(OtterEngine::Engine *oe, T &obj);
	std::string getName();
	int getPriority();

private:
	std::string _name;
	int (T:: *_function)(OtterEngine::Engine *oe);
	bool (T:: *_condition)(OtterEngine::Engine *oe);
	int _priority;
};

template<class T>
OtterEngine::Event<T>::Event(std::string name, int (T::*function)(OtterEngine::Engine *), bool (T::*condition)(OtterEngine::Engine *), int priority) : _name(name), _function(function), _condition(condition), _priority(priority)
{

}

template<class T>
OtterEngine::Event<T>::~Event()
{

}

template<class T>
int OtterEngine::Event<T>::reaction(OtterEngine::Engine *oe, T &obj)
{
	return ((obj.*_function)(oe));
}

template<class T>
bool OtterEngine::Event<T>::verification(OtterEngine::Engine *oe, T &obj)
{
	return ((obj.*_condition)(oe));
}

template<class T>
std::string OtterEngine::Event<T>::getName()
{
	return _name;
}

template<class T>
int OtterEngine::Event<T>::getPriority()
{
	return _priority;
}


template <class T>
void addEvent(std::vector<OtterEngine::Event<T>> &events, OtterEngine::Event<T> event)
{
	std::size_t i;
	
	for (i = 0; (std::size_t)i < events.size(); i++)	{
		if(event.getName() == events[i].getName())
			return;
		if (event.getPriority() > events[i].getPriority())
			break;
	}
	events.insert(events.begin() + i, event);
}

template <class T>
void removeEvent(std::vector<OtterEngine::Event<T>> &events, std::string name)
{
	std::size_t i;

	for (i = 0; i < events.size(); i++)     {
		if(name == events[i].getName())
			break;
	}
	if (i == events.size())
		return;
	events.erase(events.begin() +  i);
}
