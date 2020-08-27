#include <string>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <thread>

#include "Client.hpp"
#include "InputManager.hpp"
#include "WindowManager.hpp"

#include <SFML/Graphics.hpp>

int main(int ac, char **av)
{
	try {
		if (ac != 3) {
			std::cout << "./client serverIp serverPort" << std::endl;
			exit(84);
		}

		std::string buff;
		std::chrono::time_point<std::chrono::system_clock> now;
		std::chrono::time_point<std::chrono::system_clock> tmp;
		std::chrono::duration<float, std::milli> diff;
		float deltaTime;

		Client client;
		WindowManager *window = WindowManager::getInstance();
		window->setView(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2), sf::Vector2f(window->getSize().x, window->getSize().y));

		std::thread r([&] { client.setup(); });
		
		if (!client.connectToServer(av[1], std::stoi(av[2]))) {
			window->close();
			r.join();
			return 84;
		}
		while (!client.getMessageFromQueue(buff) || buff.compare(0, 5, "join:") != 0);
		client.setGameId(std::stoi(buff.substr(5, std::string::npos)));

		while (window->isOpen()) {
			tmp = std::chrono::system_clock::now();
			diff = tmp - now;
	    	now = tmp;
	    	deltaTime = diff.count();

			window->clear();
			client.update(deltaTime);
			window->display();

			if (window->hasFocus())
				client.handleInput(deltaTime);
			
			if (client.getMessageFromQueue(buff)) {
				//std::cout << "read " << buff << std::endl;
				client.process(buff);
			}
			//client.draw();
		}
		r.join();
	} catch (...) {

	}

	return 0;
}