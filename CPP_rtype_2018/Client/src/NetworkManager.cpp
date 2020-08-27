//
// EPITECH PROJECT, 2018
// client
// File description:
// network manager
//

#include <cstring>
#include <iostream>
#include <unistd.h>

#include "NetworkManager.hpp"
#include "WindowManager.hpp"

void NetworkManager::setup()
{
	std::string buff;
	WindowManager *w = WindowManager::getInstance();

	if (!this->bind()) {
		std::cout << "setup: fail bind" << std::endl;
		_port = 1;
		return;
	}
	_socket.setBlocking(false);
	while (w->isOpen()) {
		if (this->receive(buff))
			_inQueue.push(buff);
		if (_outQueue.tryPop(buff))
			this->send(buff, _serverIp, _serverPort);
	}
}

bool NetworkManager::getMessageFromQueue(std::string &buff)
{
    return _inQueue.tryPop(buff);
}

NetworkManager::NetworkManager() 
: _serverIp("127.0.0.1"), _serverPort(0), _port(0), _connected(false), _id(0)
{}

NetworkManager::~NetworkManager()
{
	disconnect();
}

std::size_t NetworkManager::getId() const
{
	return _id;
}

bool NetworkManager::receive(std::string &buffer)
{
	char data[100];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short port;

	memset(data, 0, 100);
	if (_socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
		return false;
	buffer = std::string(data, received);

	return true;
}

bool NetworkManager::connectToServer(sf::IpAddress ip, unsigned short port)
{
	std::cout << "Connecting to server..." << std::endl;
	while (_port == 0);
	if (!this->send("Connect", ip, port)) {
		std::cout << "Can't connect to server, check ip and port" << std::endl;
		return false;
	}
	std::string ret = "";

	for (int i = 0; i < 5; i++) {
		std::cout << "Waiting for server response (" << i << ")" << std::endl;
		if (this->getMessageFromQueue(ret))
			break;
		sleep(1);
	}
	if (ret.empty()) {
		std::cout << "No response from server, please check ip and port" << std::endl;
		return false;
	}
	if (ret.compare(0, 3, "OK ") != 0) {
		std::cout << "Invalid response from server: " << ret << std::endl;
		return false;	
	}
	std::cout << "Connexion OK" << std::endl;
	_connected = true;
	_id = std::stoi(ret.substr(3, std::string::npos));
	_serverIp = ip;
	_serverPort = port;
	return true;
}

bool NetworkManager::isConnected() const
{
	return _connected;
}

void NetworkManager::disconnect()
{
	if (!_connected)
		return;

	this->send("Disconnect " + std::to_string(_id), _serverIp, _serverPort);
	_socket.setBlocking(true);
	_id = 0;
	_serverIp = "127.0.0.1";
	_serverPort = 0;
	_connected = false;
}

void NetworkManager::sendToServer(std::string data)
{
	if (!_connected)
		return;
	//data = std::to_string(_id) + ":" + data;
	_outQueue.push(data);
}

bool NetworkManager::send(std::string data, sf::IpAddress ip, unsigned short port)
{
	if (data.size() > 100) {//faut split si sup à 1400 octets
		std::cout << "Message with more than 100 char cannot be sent for the moment (not implemented)\n";
		return false;
	}

	if (_socket.send(data.c_str(), data.size(), ip, port) != sf::Socket::Done)
		return false;
	return true;
}

bool NetworkManager::bind()
{
	try {
		if (_socket.getLocalPort() == 0 && _socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
			std::cout << "Socket bind error" << std::endl;
			return false;
		}
		_port = _socket.getLocalPort();
		return true;
	} catch(...) {
		return false;
	}
}