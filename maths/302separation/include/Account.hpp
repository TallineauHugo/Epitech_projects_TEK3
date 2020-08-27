//
// EPITECH PROJECT, 2018
// 302separation
// File description:
// account
//

#pragma once

#include <map>

class Account
{
public:
	Account(std::string name);
	~Account();
public:
	void addFriend(std::string friendName, Account *acc);
	std::string getName();
	Account *getFriend(std::string friendName);
	bool isFriendWith(std::string);
	int distFrom(std::string name);
private:
	std::map<std::string, Account *> _friendsMap;
	std::string _accName;
	bool _testing = false;
};
