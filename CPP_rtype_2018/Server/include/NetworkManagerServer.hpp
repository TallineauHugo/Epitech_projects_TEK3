//
// EPITECH PROJECT, 2018
// server
// File description:
// udp server
//

#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <utility>
#include <map>

#include "Logger.hpp"
#include "ClientServer.hpp"
#include "SafeQueue.hpp"

extern bool VERBOSE;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
public:
	void setup(std::string ip, std::string port);
	void sendToClient(std::size_t id, std::string msg);
	void sendToAllClient(std::string msg);
	bool getMessageFromQueue(std::size_t queueId, std::string &buff);

	void connect(std::string arg);
	void disconnect(std::string arg);
	bool isConnected(std::size_t id) const;

	std::map<std::size_t, Client*> getClientMap() const;
private:
	void initRecognizedCommands();
	void wait();
	void handleReceive(const boost::system::error_code& error, size_t bytes_transferred);

	

	void sendTo(std::string msg, boost::asio::ip::address ip, unsigned short port);
	void sendTo(std::string msg, boost::asio::ip::udp::endpoint endpoint);

	void resetId();
	std::size_t getNextId();


private:
	Logger logger;
	std::map<std::size_t, SafeQueue<std::string>> _queues;

	//dialog
	boost::asio::io_service _ioService;
    boost::asio::ip::udp::socket _socket{_ioService};
    boost::array<char, 1024> _receivedBuffer;
    boost::asio::ip::udp::endpoint _remoteEndpoint;

    //client handling
    std::size_t _id;
    
    std::map<std::size_t, Client*> _clients;
    std::map<std::string, std::function<void(std::string)>> _func;
};