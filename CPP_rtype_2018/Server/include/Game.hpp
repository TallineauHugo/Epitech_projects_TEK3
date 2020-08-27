//
// EPITECH PROJECT, 2018
// server
// File description:
// game
//

#pragma once

#include <map>
#include <list>
#include <functional>
#include <chrono>


#include "Player.hpp"
#include "Object.hpp"
#include "ClientServer.hpp"

class Server;

class Game 
{
public:
	Game(Server *server, std::list<Client> clients, std::size_t id);
	~Game();
public:
	void start();
private:
	void process(std::string buff);
	void update();
	void sendDataToClients();
	void move(std::string id, std::string arg);
	void shoot(std::string id, std::string arg);
	void bomb(std::string id, std::string arg);
	void destroyObject(std::size_t id);
	std::size_t getNextId();
private:
	OtterEngine::Engine _oe;
	Server *_server;
	
	std::list<Client> _clients;
	std::map<std::string, std::function<void(std::string, std::string)>> _func;
	std::size_t _id;
};
