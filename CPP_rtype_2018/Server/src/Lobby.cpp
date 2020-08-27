#include "Lobby.hpp"
#include "Server.hpp"

Lobby::Lobby(std::string name, Server *server, std::size_t id)
: _neededPlayer(4), _id(id), _name(name), _server(server), _state(Lobby::state::WAITING)
{
	if (VERBOSE)
		this->logger.printLog("new lobby created: " + name);
}

Lobby::~Lobby()
{

}
#include <iostream>
void Lobby::run()
{
	int playerReady;
	std::list<Client>::iterator it;

	while (1) {
		playerReady = 0;
		it = this->_clients.begin();
		while (it != this->_clients.end()) {
			if (!_server->isConnected(it->getId()))
				_clients.erase(it);
			else if (it->isReady())
				playerReady++;
			it++;
		}
		if (playerReady == this->_neededPlayer) {
			if (VERBOSE)
				logger.printLog("Lobby " + std::to_string(this->getId()) + "<" + this->_name + "> starting the game !");
			this->_state = Lobby::state::RUNNING;
			this->_game = new Game(_server, _clients, this->getId());
			_game->start();
			break;
		}
		else if (VERBOSE)
			std::cout << playerReady << " player ready, " << this->_neededPlayer - playerReady << " less to go\n";
		sleep(1);
	}
}

void Lobby::addClient(Client client)
{
	logger.printLog("Client: " + std::to_string(client.getId()) + " connected to lobby: " + this->_name);
	this->_clients.push_back(client);
}

void Lobby::rename(std::string name)
{
	this->_name = name;
}

bool Lobby::isFull() const
{
	return _clients.size() >= (std::size_t)_neededPlayer;
}

std::string Lobby::getName() const
{
	return this->_name;
}

int Lobby::getConnectedClient() const
{
	return this->_clients.size();
}

Lobby::state Lobby::getState() const
{
	return this->_state;
}

std::size_t Lobby::getId() const
{
	return this->_id;
}