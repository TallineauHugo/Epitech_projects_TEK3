//
// EPITECH PROJECT, 2018
// client
// File description:
// network manager
//

#pragma once

#include <string>
#include <SFML/Network.hpp>

#include "SafeQueue.hpp"

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
public:
	void setup();

	void sendToServer(std::string data);
	void disconnect();

	bool connectToServer(sf::IpAddress ip, unsigned short port);
	bool isConnected() const;
	bool getMessageFromQueue(std::string &buff);

	std::size_t getId() const;
private:
	bool send(std::string data, sf::IpAddress ip, unsigned short port);
	bool receive(std::string &buffer);
	bool bind();
private:
	SafeQueue<std::string> _inQueue;
	SafeQueue<std::string> _outQueue;
	sf::UdpSocket _socket;
	sf::IpAddress _serverIp;
	unsigned short _serverPort;
	unsigned short _port;

	bool _connected;
	std::size_t _id;
};