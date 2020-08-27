//
// EPITECH PROJECT, 2018
// client
// File description:
// client
//

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "NetworkManager.hpp"
#include "Object.hpp"
#include "OtterEngine.hpp"
#include "Gauge.hpp"

class Client
{
public:
	Client();
	~Client();
public:
	//connection
	bool connectToServer(sf::IpAddress ip, unsigned short port);
	void disconnect();
	void setup();

	//dialog
	bool getMessageFromQueue(std::string &buff);
	void sendToServer(std::string msg);

	//process
	void setGameId(std::size_t id);
	void process(std::string buff);
	void handleInput(float deltaTime);
	void update(float deltaTime);

	void createObject(std::size_t id, Vector2d pos, std::string type);
private:

private:
	//std::map<std::size_t, OtterEngine::Object*> _objects;
	//std::map<std::string, std::function<void(std::string)>> _func;
	OtterEngine::Engine _oe;
	NetworkManager _network;
	bool _dir[4];
	bool _shoot;
	bool _bomb;
	std::size_t _id;
	std::size_t _gameId;

	OtterEngine::FixedSprite *_background;
};