#include <iostream>

#include "NetworkManagerServer.hpp"
#include "Parser.hpp"

void NetworkManager::setup(std::string ip, std::string port)
{
    try {
        _socket.open(boost::asio::ip::udp::v4());
        _socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), std::stoi(port)));
        wait();

        if (VERBOSE) {
            logger.printLog("Server address: " + _socket.local_endpoint().address().to_string());
            logger.printLog("Server port: " + std::to_string(_socket.local_endpoint().port()));
        }
        _ioService.run();
        if (VERBOSE)
            logger.printLog("Server close");
    } catch (...) {
        if (VERBOSE)
            logger.printLog("Definitively an expected error, everything is working fine, we just exit 84 for fun");
        exit(84);
    }
}

void NetworkManager::sendToClient(std::size_t id, std::string msg)
{
    if (_clients.find(id) != _clients.end())
        this->sendTo(msg, _clients[id]->getEndpoint());
}

void NetworkManager::sendToAllClient(std::string msg)
{
    std::map<std::size_t, Client*>::iterator it = _clients.begin();

    while (it != _clients.end()) {
        this->sendTo(msg, it->second->getEndpoint());
        it++;
    }
}

bool NetworkManager::getMessageFromQueue(std::size_t queueId, std::string &buff)
{
    if (_queues.find(queueId) == _queues.end())
        return false;
    return _queues[queueId].tryPop(buff);
}

//Commands
bool NetworkManager::isConnected(std::size_t id) const
{
    return (_clients.find(id) != _clients.end());
}
void NetworkManager::connect(std::string arg)
{
    std::size_t id = this->getNextId();

    _clients[id] = new Client(id, _remoteEndpoint);
    //_queue.push(std::string(std::to_string(id) + ":create " + std::to_string(id)));
    this->sendTo("OK " + std::to_string(id), _remoteEndpoint);
    if (VERBOSE)
        logger.printLog("Player " + std::to_string(id) + " connect to server: " + std::to_string(_clients.size()) + " online");
    (void)arg;
}

void NetworkManager::disconnect(std::string arg)
{
    std::size_t id;

    try {
        id = std::stoi(arg);
    
        if (_clients.find(id) != _clients.end()) {
            _clients.erase(id);
            if (VERBOSE)
                logger.printLog("Client " + std::to_string(id) + " disconnect: " + std::to_string(_clients.size()) + " online");
        }
    } catch (...) {
        return;
    }
}

//private
void NetworkManager::wait()
{
    _socket.async_receive_from(boost::asio::buffer(_receivedBuffer),
        _remoteEndpoint,
        boost::bind(&NetworkManager::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void NetworkManager::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) 
{
    try {
        if (error) {
            if (VERBOSE)
                logger.printLog("Receive failed: " + error.message());
            return;
        }
        std::string msg(_receivedBuffer.begin(), _receivedBuffer.begin() + bytes_transferred);
        std::pair<std::string, std::string> split = Parser::getInstance()->splitStringToPair(msg, ' ');
        std::string arg;
        std::size_t gameId = 0;

        if (_func.find(split.first) != _func.end())
            _func[split.first](split.second);
        else {
            split = Parser::getInstance()->splitStringToPair(msg, '/');
            gameId = std::stoi(split.first);
            if (_queues.find(gameId) == _queues.end())
                _queues[gameId] = SafeQueue<std::string>();
            _queues[gameId].push(split.second);
        }
    } catch (...) {
        
    }

    wait();
}

void NetworkManager::sendTo(std::string msg, boost::asio::ip::address ip, unsigned short port)
{
    boost::system::error_code err;
    boost::asio::ip::udp::endpoint remoteEndpoint;

    remoteEndpoint = boost::asio::ip::udp::endpoint(ip, port);

    _socket.send_to(boost::asio::buffer(msg.c_str(), msg.size()), remoteEndpoint, 0, err);
}

void NetworkManager::sendTo(std::string msg, boost::asio::ip::udp::endpoint endpoint)
{
    boost::system::error_code err;

    _socket.send_to(boost::asio::buffer(msg.c_str(), msg.size()), endpoint, 0, err);
}

void NetworkManager::resetId()
{
    _id = 0;
}

std::size_t NetworkManager::getNextId()
{
    while (_clients.find(_id) != _clients.end())
        _id++;
    return _id;
}

std::map<std::size_t, Client*> NetworkManager::getClientMap() const
{
    return _clients;
}

void NetworkManager::initRecognizedCommands()
{
    _func["Connect"] = std::bind(&NetworkManager::connect, this, std::placeholders::_1);
    _func["Disconnect"] = std::bind(&NetworkManager::disconnect, this, std::placeholders::_1);
}

NetworkManager::NetworkManager() : _id(0)
{
    initRecognizedCommands();
}

NetworkManager::~NetworkManager()
{
    _ioService.stop();
}
