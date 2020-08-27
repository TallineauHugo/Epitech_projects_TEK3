//
// EPITECH PROJECT, 2018
// server
// File description:
// client
//

#include "ClientServer.hpp"

Client::Client(std::size_t id, boost::asio::ip::udp::endpoint endpoint)
: _id(id), _endpoint(endpoint), _ready(false)
{}

Client::~Client()
{}

std::size_t Client::getId() const
{
	return _id;
}

boost::asio::ip::udp::endpoint Client::getEndpoint() const
{
	return _endpoint;
}

boost::asio::ip::address Client::getIpAddress() const
{
	return _endpoint.address();
}

unsigned short Client::getPort() const
{
	return _endpoint.port();
}

bool Client::isReady() const
{
	return this->_ready;
}

void Client::makeReady()
{
	this->_ready = true;
}