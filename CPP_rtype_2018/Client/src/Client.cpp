//
// EPITECH PROJECT, 2018
// client
// File description:
// client
//

#include <cstdio>
#include <iostream>
#include "Client.hpp"
#include "InputManager.hpp"
#include "WindowManager.hpp"
#include "SpritesManager.hpp"
#include "Player.hpp"
#include "ZigZagEnnemy.hpp"
#include "Bullet.hpp"
#include "Energy.hpp"
#include "Camp.hpp"

void Client::setGameId(std::size_t id)
{
	_gameId = id;
}

void Client::setup()
{
	_network.setup();
}

void Client::handleInput(float deltaTime)
{
	InputManager *input = InputManager::getInstance();
	Vector2d pos;
	
	OtterEngine::Object *obj = _oe.getObjectById(_id);
	float speed = 0.5;

	if (input->isKeyPressed(sf::Keyboard::Escape)) {
		WindowManager::getInstance()->close();
		return;
	}
	if (!obj)
		return;
	if (input->isKeyPressed(sf::Keyboard::Z) ||
		input->isKeyPressed(sf::Keyboard::Up)) {
		pos = obj->getPos();
		obj->setPos(Vector2d(pos.x, pos.y - speed * deltaTime));
		if (_dir[UP] == false) {
			_dir[UP] = true;
			this->sendToServer(std::to_string(_network.getId()) + ":" + "move up start");
		}
	}
	else if (_dir[UP]) {
		_dir[UP] = false;
		this->sendToServer(std::to_string(_network.getId()) + ":" + "move up stop");
	}
	if (input->isKeyPressed(sf::Keyboard::D) ||
		input->isKeyPressed(sf::Keyboard::Right)) {
		pos = obj->getPos();
		obj->setPos(Vector2d(pos.x + speed * deltaTime, pos.y));
		if (_dir[RIGHT] == false) {
			_dir[RIGHT] = true;	
			this->sendToServer(std::to_string(_network.getId()) + ":" + "move right start");
		}
	}
	else if (_dir[RIGHT]) {
		_dir[RIGHT] = false;
		this->sendToServer(std::to_string(_network.getId()) + ":" + "move right stop");
	}
	if (input->isKeyPressed(sf::Keyboard::S) ||
		input->isKeyPressed(sf::Keyboard::Down)) {
		pos = obj->getPos();
		obj->setPos(Vector2d(pos.x, pos.y + speed * deltaTime));
		if (_dir[DOWN] == false) {
			_dir[DOWN] = true;
			this->sendToServer(std::to_string(_network.getId()) + ":" + "move down start");
		}
	}
	else if (_dir[DOWN]) {
		_dir[DOWN] = false;
		this->sendToServer(std::to_string(_network.getId()) + ":" + "move down stop");
	}
	if (input->isKeyPressed(sf::Keyboard::Q) ||
		input->isKeyPressed(sf::Keyboard::Left)) {
		pos = obj->getPos();
		obj->setPos(Vector2d(pos.x - speed * deltaTime, pos.y));
		if (_dir[LEFT] == false) {
			_dir[LEFT] = true;
			this->sendToServer(std::to_string(_network.getId()) + ":" + "move left start");
		}
	}
	else if (_dir[LEFT]) {
		_dir[LEFT] = false;
		this->sendToServer(std::to_string(_network.getId()) + ":" + "move left stop");
	}
	if (input->isKeyPressed(sf::Keyboard::Space)) {
		if (_shoot == false) {
			_shoot = true;
			this->sendToServer(std::to_string(_network.getId()) + ":" + "shoot start");
		}
	}
	else if (_shoot) {
		_shoot = false;
		this->sendToServer(std::to_string(_network.getId()) + ":" + "shoot stop");
	}
	if (input->isKeyPressed(sf::Keyboard::B)) {
		if (_bomb == false) {
			_bomb = true;
			this->sendToServer(std::to_string(_network.getId()) + ":" + "bomb start");
		}
	}
	else if (_bomb) {
		_bomb = false;
		this->sendToServer(std::to_string(_network.getId()) + ":" + "bomb stop");
	}
}

void Client::update(float deltaTime)
{
	(void)deltaTime;
	_oe.update();
	/*std::vector<OtterEngine::Object*> obj = _oe.getObjs();
	std::vector<OtterEngine::Object*>::iterator it = obj.begin();
	Vector2d pos;
	Vector2d aim;
	float speed = 1.0;

	while (it != obj.end()) {
		if ((*it)->getId() != _id) {
			pos = (*it)->getPos();
			aim = (*it)->getAim();
			if ((int)pos.x != (int)aim.x) {
				pos.x = (pos.x < aim.x) ? pos.x + speed * deltaTime : pos.x - speed * deltaTime;
			}
			if ((int)pos.y != (int)aim.y) {
				pos.y = (pos.y < aim.y) ? pos.y + speed * deltaTime : pos.y - speed * deltaTime;
			}
			pos.x = (int)pos.x;
			pos.y = (int)pos.y;
			(*it)->setPos(pos);
			
		}
		it++;
	}*/
}

void Client::process(std::string buff)
{
	std::string posx;
	std::string posy;
	std::string name;
	std::size_t id;
	OtterEngine::Object *obj;

	id = std::stoi(buff.substr(0, buff.find(':')));
	buff = buff.substr(buff.find(':') + 1, std::string::npos);
	if (buff.compare(0, 6, "delete") == 0) {
		obj = _oe.getObjectById(id);
		if (!obj || !obj->getSprite())
			return;
		OtterEngine::SpritesManager::getInstance()->removeSprite(_oe.getObjectById(id)->getSprite());
		_oe.removeObjectById(id);
		return;
	}
	name = buff.substr(0, buff.find(':'));
	buff = buff.substr(buff.find(':') + 1, std::string::npos);
	posx = buff.substr(0, buff.find(','));
	posy = buff.substr(buff.find(',') + 1, std::string::npos);

	if (_oe.getObjectById(id) == nullptr) {
		createObject(id, Vector2d(std::stoi(posx), std::stoi(posy)), name);
		return;
	}
	if (id == _id)
		_oe.getObjectById(id)->setPos(Vector2d(std::stoi(posx), std::stoi(posy)));
	else
		_oe.getObjectById(id)->setPos(Vector2d(std::stoi(posx), std::stoi(posy)));
}

void Client::createObject(std::size_t id, Vector2d pos, std::string type)
{
	if (type.compare(0, 6, "Player") == 0)
		_oe.addObject(new Player(pos, id));
	else if (type.compare(0, 12, "ZigZagEnnemy") == 0)
		_oe.addObject(new ZigZagEnnemy(pos, id));
	else if (type.compare(0, 6, "Energy") == 0)
		_oe.addObject(new Energy(pos, 25, id));
	else if (type.compare(0, 6, "Bullet") == 0)
		_oe.addObject(new Bullet(pos, Vector2d(1000, 0), CAMP::ALLY, id));
}

bool Client::getMessageFromQueue(std::string &buff)
{
	return _network.getMessageFromQueue(buff);
}

bool Client::connectToServer(sf::IpAddress ip, unsigned short port)
{
	_network.connectToServer(ip, port);

	_id = _network.getId();
	_oe.addObject(new Player(Vector2d(100, 100), _id));

	return _network.isConnected();
}

void Client::disconnect()
{
	_network.disconnect();
}

void Client::sendToServer(std::string msg)
{
	msg = std::to_string(_gameId) + "/" + msg;
	_network.sendToServer(msg);
}

Client::Client() : _id(0), _gameId(0)
{
	_dir[UP] = false;
	_dir[RIGHT] = false;
	_dir[DOWN] = false;
	_dir[LEFT] = false;
	_shoot = false;
	_bomb = false;
	_background = new OtterEngine::FixedSprite;
	_background->loadSpriteFromFile("ressources/texture/background.png");
	_background->setSize(Vector2d(WindowManager::getInstance()->getSize()));
	_background->setPosition({_background->getSize().x / 2, _background->getSize().y / 2});
	OtterEngine::SpritesManager::getInstance()->addSprite(0, _background);
}

Client::~Client()
{
	disconnect();
}