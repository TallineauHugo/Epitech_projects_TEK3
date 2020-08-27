//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// account
//

#include "Account.hpp"

Account::Account(std::string name) : _accName(name)
{
}

Account::~Account()
{}

void Account::addFriend(std::string friendName, Account *acc)
{
	if (_friendsMap.find(friendName) == _friendsMap.end())
		_friendsMap[friendName] = acc;
}

Account *Account::getFriend(std::string friendName)
{	
	if (_friendsMap.find(friendName) != _friendsMap.end())
		return _friendsMap[friendName];
	return nullptr;
}

std::string Account::getName()
{	
	return _accName;
}

bool Account::isFriendWith(std::string acc)
{	
	return (getFriend(acc) != nullptr) ? true : false;
}

int Account::distFrom(std::string name)
{
	std::map<std::string, Account*>::iterator it = _friendsMap.begin();
	int dist = -1;
	int tmp;

	if (_testing)
		return -1;
	if (this->isFriendWith(name))
		return 1;
	else {
		_testing = true;
		while (it != _friendsMap.end()) {
			tmp = it->second->distFrom(name);
			if ((tmp < dist || dist == -1) && tmp != -1)
				dist = tmp;
			it++;
		}
		_testing = false;
	}
	if (dist == -1)
		return -1;
	dist++;
	return dist;
}
