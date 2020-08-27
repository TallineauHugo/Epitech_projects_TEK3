//
// EPITECH PROJECT, 2018
// server
// File description:
// game
//

#include <boost/asio.hpp>
#include <iostream>

#include "Game.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Player.hpp"
#include "ZigZagEnnemy.hpp"
#include "Id.hpp"

Game::Game(Server *server, std::list<Client> clients, std::size_t gameId)
: _server(server), _clients(clients), _id(gameId)
{
	std::list<Client>::iterator it = clients.begin();
	std::size_t i = 0;
	std::size_t id = 0;
	Player *player;

	while (it != clients.end()) {
		id = it->getId();
		player = new Player(Vector2d(10 + i * 200, 300), id);
		_oe.addObject(player);
		i++;
		it++;
	}
	_func["move"] = std::bind(&Game::move, this, std::placeholders::_1, std::placeholders::_2);
	_func["shoot"] = std::bind(&Game::shoot, this, std::placeholders::_1, std::placeholders::_2);
	_func["bomb"] = std::bind(&Game::bomb, this, std::placeholders::_1, std::placeholders::_2);

	_oe.setGraphicalMode(false);
}

Game::~Game()
{}

void Game::move(std::string id, std::string arg)
{
	Parser *parser = Parser::getInstance();
	std::pair<std::string, std::string> split;
	std::size_t sid;
	OtterEngine::Object *obj;

	try {
		sid = std::stoi(id);
		obj = _oe.getObjectById(sid);
		if (obj == nullptr)
			return;
		split = parser->splitStringToPair(arg, ' ');

		if (split.first.compare(0, 2, "up") == 0) {
			if (split.second.compare(0, 5, "start") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StartMoveUp();
			else if (split.second.compare(0, 4, "stop") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StopMoveUp();
		}

		else if (split.first.compare(0, 5, "right") == 0) {
			if (split.second.compare(0, 5, "start") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StartMoveRight();
			else if (split.second.compare(0, 4, "stop") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StopMoveRight();
		}

		else if (split.first.compare(0, 4, "down") == 0) {
			if (split.second.compare(0, 5, "start") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StartMoveDown();
			else if (split.second.compare(0, 4, "stop") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StopMoveDown();
		}

		else if (split.first.compare(0, 4, "left") == 0) {
			if (split.second.compare(0, 5, "start") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StartMoveLeft();
			else if (split.second.compare(0, 4, "stop") == 0
				&& dynamic_cast<Player*>(obj) != nullptr)
				dynamic_cast<Player*>(obj)->StopMoveLeft();
		}
	} catch (...) {

	}
}

void Game::shoot(std::string id, std::string arg)
{
	std::size_t sid;
	std::vector<OtterEngine::Object*> vObj = _oe.getObjs();
	OtterEngine::Object *obj;

	try {
		sid = std::stoi(id);
		obj = _oe.getObjectById(sid);
		if (!obj)
			return;
		if (arg.compare(0, 5, "start") == 0)
			dynamic_cast<Player*>(_oe.getObjectById(sid))->StartShoot();
		else if (arg.compare(0, 4, "stop") == 0)
			dynamic_cast<Player*>(_oe.getObjectById(sid))->StopShoot();
	} catch (...) {

	}
}

void Game::bomb(std::string id, std::string arg)
{
	std::size_t sid;
	std::vector<OtterEngine::Object*> vObj = _oe.getObjs();
	OtterEngine::Object *obj;

	try {
		sid = std::stoi(id);
		obj = _oe.getObjectById(sid);
		if (!obj)
			return;
		if (arg.compare(0, 5, "start") == 0)
			dynamic_cast<Player*>(_oe.getObjectById(sid))->StartBomb();
		else if (arg.compare(0, 4, "stop") == 0)
			dynamic_cast<Player*>(_oe.getObjectById(sid))->StopBomb();
	} catch (...) {

	}	
}

void Game::start()
{
	std::chrono::time_point<std::chrono::system_clock> now;
	std::chrono::time_point<std::chrono::system_clock> old;
	std::chrono::duration<float, std::milli> diff;
	std::string buff;
	std::size_t id = 0;
	float deltaTime = 0;
	float totalTime = 0;

	id = getNextId();
	_oe.addObject(new ZigZagEnnemy(Vector2d(2000, 300), id));

	/*id = getNextId();
	_oe.addObject(new ZigZagEnnemy(Vector2d(2400, 600), id));

	id = getNextId();
	_oe.addObject(new ZigZagEnnemy(Vector2d(2900, 900), id));*/

	old = std::chrono::system_clock::now();
	float tick = 0.05;
	while (_clients.size() != 0) {
		now = std::chrono::system_clock::now();
		diff = now - old;
		old = now;
		deltaTime = diff.count();
		totalTime += (deltaTime / 1000);

		if (_server->getMessage(_id, buff))
			this->process(buff);
		if (totalTime >= tick)
			this->update();
		_oe.update();

		if (totalTime >= tick) {
			this->sendDataToClients();
			totalTime = totalTime - tick;
		}
	}
	std::cout << "End of game" << std::endl;
}

void Game::process(std::string buff)
{
	Parser *parser = Parser::getInstance();
	std::pair<std::string, std::string> split = parser->splitStringToPair(buff, ':');
	std::string id;

	id = split.first;
	split = parser->splitStringToPair(split.second, ' ');
    if (_func.find(split.first) != _func.end())
        _func[split.first](id, split.second);
}

void Game::update()
{
	std::list<Client>::iterator it = _clients.begin();
	std::size_t id;

	while (it != _clients.end()) {
		id = it->getId();
		if (!_server->isConnected(id)) {
			it = _clients.erase(it);
			_oe.removeObjectById(id);
			//this->destroyObject(id);
		}
		else
			it++;
	}
	std::list<std::size_t> rm = _oe.getRemovedList();
	std::list<std::size_t>::iterator it2 = rm.begin();
	while (it2 != rm.end()) {
		this->destroyObject(*it2);
		it2++;
	}
}

void Game::destroyObject(std::size_t id)
{
	std::list<Client>::iterator it = _clients.begin();

	while (it != _clients.end()) {
		//std::cout << "send " << id << ":delete to " << it->getId() << std::endl;
		_server->sendToClient(it->getId(), std::to_string(id) + ":delete");
		it++;
	}
}

void Game::sendDataToClients()
{
	std::list<Client>::iterator it2 = _clients.begin();
	Vector2d pos;
	std::string buff;
	std::string name;
	std::size_t start;
	std::size_t goal;
	std::vector<OtterEngine::Object*> vObj = _oe.getObjs();
	std::vector<OtterEngine::Object*>::iterator it = vObj.begin();

	while (it != vObj.end()) {
			pos = (*it)->getPos();
			name = (*it)->getName();
			goal = name.rfind("::", std::string::npos);
			start = name.rfind("::", goal - 1) + 2;
			name = name.substr(start, goal - start);
			buff = std::to_string((*it)->getId()) + 
				":" + name + ":"
				+ std::to_string((int)pos.x) + "," + 
				std::to_string((int)pos.y);

			it2 = _clients.begin();
			//std::cout << "send " << buff << std::endl;
			while (it2 != _clients.end()) {
				_server->sendToClient(it2->getId(), buff);
				it2++;
			}
		it++;
	}
}

std::size_t Game::getNextId()
{
	std::vector<OtterEngine::Object*> vObj = _oe.getObjs();
	std::vector<OtterEngine::Object*>::iterator it2;
	std::size_t id = Id::getInstance()->getNextId();

	it2 = vObj.begin();
	while (it2 != vObj.end()) {
		if ((*it2)->getId() == id) {
			id = Id::getInstance()->getNextId();
			it2 = vObj.begin();
		}
		else
			it2++;
	}
    
    return id;
}