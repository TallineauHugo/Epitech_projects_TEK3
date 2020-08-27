//
// EPITECH PROJECT, 2018
// server
// File description:
// server
//

#pragma once

#include <map>
#include <list>

#include "NetworkManagerServer.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Lobby.hpp"

class Server
{
public:
	Server();
	~Server();
public:
	void setup(std::string ip, std::string port);
	void run();

	void process(std::string buff);
	//void update(float deltaTime);
	//void sendDataToClients();
	bool getMessage(std::size_t index, std::string &buff);
	bool isConnected(std::size_t id) const;
	void sendToClient(std::size_t id, std::string msg);
private:
	void initRecognizedCommands();
	//void create(std::string id, std::string arg);
	//void move(std::string id, std::string arg);
	void createLobby(std::string name, std::size_t id);
	void joinLobby(Client client, std::string name);
	void runLobby(Lobby lobby);
private:
	Logger _logger;
	NetworkManager _network;

	std::list<Lobby> _lobbys;

	std::map<std::string, std::function<void(std::string, std::string)>> _func;
	//std::map<std::size_t, Player*> _players;
};