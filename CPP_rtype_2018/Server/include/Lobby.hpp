#pragma once

#include <list>

#include "ClientServer.hpp"
#include "Logger.hpp"
#include "Game.hpp"

extern bool VERBOSE;

class Server;

class Lobby
{
	enum state {
		WAITING,
		RUNNING
	};
public:
	Lobby(std::string, Server *server, std::size_t);
	~Lobby();

	void run();
	void addClient(Client client);
	void rename(std::string);
	bool isFull() const;
	int getConnectedClient() const;
	std::string getName() const;
	state getState() const;
	std::size_t getId() const;
	std::thread runThread() {return std::thread(&Lobby::run, this);}
private:
	int _neededPlayer;
	std::size_t _id;
	std::string _name;
	std::list<Client> _clients;
	Game *_game;
	Server *_server;
	state _state;
	Logger logger;
};
