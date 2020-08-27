//
// EPITECH PROJECT, 2018
// server
// File description:
// server
//

#include "Server.hpp"
#include "Parser.hpp"
#include "Game.hpp"
#include <iostream>

void Server::run()
{
	std::map<std::size_t, Client*> clients;
	std::map<std::size_t, Client*>::iterator it;
	std::list<Lobby>::iterator it2;
	std::map<std::size_t, Client*> inLobby;
	std::size_t idLobby = 0;
	std::list<std::thread> _threads;

	this->createLobby("lobby" + std::to_string(idLobby), idLobby);
	idLobby++;
	while (1) {
		clients = _network.getClientMap();
		it = clients.begin();
		while (it != clients.end()) {
			if (inLobby.find(it->first) == inLobby.end()) {
				inLobby[it->first] = it->second;

				it2 = _lobbys.begin();
				while (it2 != _lobbys.end()) {
					if (!it2->isFull()) {
						it->second->makeReady();
						this->sendToClient(it->first, "join:" + std::to_string(it2->getId()));
						this->joinLobby(*(it->second), it2->getName());
						if (it2->isFull())
							//_threads.push_back(std::thread([=] {it2->run();}));
							it2->run(); //faut threader
						break;
					}
					it2++;
				}
				if (it2 == _lobbys.end()) {
					this->createLobby("lobby" + std::to_string(idLobby), idLobby);
					idLobby++;
				}
			}
			it++;
		}
	}
	for (auto it = _threads.begin(); it != _threads.end(); it++) {
		it->join();
	}
}

void Server::runLobby(Lobby lobby)
{
	lobby.run();
}

void Server::setup(std::string ip, std::string port)
{
	_network.setup(ip, port);
}

void Server::process(std::string buff)
{
	Parser *parser = Parser::getInstance();
	std::pair<std::string, std::string> split = parser->splitStringToPair(buff, ':');
	std::string id;

	id = split.first;
	split = parser->splitStringToPair(split.second, ' ');
    if (_func.find(split.first) != _func.end())
        _func[split.first](id, split.second);
}

void Server::sendToClient(std::size_t id, std::string msg)
{
	this->_network.sendToClient(id, msg);
}

bool Server::isConnected(std::size_t id) const
{
	return _network.isConnected(id);
}
/*void Server::sendDataToClients()
{
	std::map<std::size_t, Player*>::iterator it = _players.begin();
	std::pair<float, float> pos;
	std::string buff;

	while (it != _players.end()) {
			pos = it->second->getPos();
			buff = std::to_string(it->second->getId()) + 
				":" + std::to_string((int)pos.first) + "," + 
				std::to_string((int)pos.second);
			_network.sendToAllClient(buff);
		it++;
	}
}*/

bool Server::getMessage(std::size_t index, std::string &buff)
{
	return _network.getMessageFromQueue(index, buff);
}

void Server::initRecognizedCommands()
{
    //_func["create"] = std::bind(&Server::create, this, std::placeholders::_1, std::placeholders::_2);
    
    //_func["createLobby"] = std::bind(&Server::createLobby, this, std::placeholders_1, std::placeholders::_2);
    //_func["joinLobby"] = std::bind(&Server::joinLobby, this, std::placeholders::_1, std::placeholders::_2)
}

/*void Server::update(float deltaTime)
{
	std::map<std::size_t, Player*>::iterator it = _players.begin();
	std::size_t id;

	while (it != _players.end()) {
		id = it->second->getId();
		if (!_network.isConnected(id))
			_players.erase(id);
		else
			it->second->update(deltaTime);
		it++;
	}
}*/

/*void Server::create(std::string id, std::string arg)
{
	try {
		_players[std::stoi(id)] = new Player(std::stoi(arg), 100, 100);
		this->sendDataToClients();
	} catch (...) {

	}
}*/

/*void Server::move(std::string id, std::string arg)
{
	try {
		_players[std::stoi(id)]->move(arg);
	} catch (...) {

	}
}*/

void Server::createLobby(std::string name, std::size_t id)
{
	_lobbys.push_back(Lobby(name, this, id));
}

void Server::joinLobby(Client client, std::string name)
{
	std::list<Lobby>::iterator it = _lobbys.begin();

	while (it != _lobbys.end()) {
		if (it->getName() == name)
			it->addClient(client);
		it++;
	}
}

/*void Server::runLobby(std::string name)
{
	std::list<Lobby>::iterator it = _lobbys.begin();

	while (it != _lobbys.end()) {
		if (it->getName() == name)
			it->run();
		it++;
	}	
}*/

Server::Server()
{
	initRecognizedCommands();
}

Server::~Server()
{}