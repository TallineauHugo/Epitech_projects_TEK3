//
// EPITECH PROJECT, 2018
// server
// File description:
// client
//

#pragma once

#include <boost/asio.hpp>

class Client
{
public:
	Client(std::size_t id, boost::asio::ip::udp::endpoint endpoint);
	~Client();
public:
	std::size_t getId() const;
	boost::asio::ip::udp::endpoint getEndpoint() const;
	boost::asio::ip::address getIpAddress() const;
	unsigned short getPort() const;
	bool isReady() const;
	void makeReady();
private:
	std::size_t _id;
	boost::asio::ip::udp::endpoint _endpoint;
	bool _ready;
};