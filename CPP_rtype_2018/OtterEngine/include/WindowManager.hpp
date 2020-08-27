//
// EPITECH PROJECT, 2018
// jam
// File description:
// windowmanager
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "View.hpp"

class WindowManager
{
public:
	static WindowManager *getInstance() {
		static WindowManager instance;

		return &instance;
	}
	~WindowManager();
	void close();
	void draw(sf::Drawable &drawable);
	void clear();
	void display();
	bool hasFocus() const;
	bool isOpen() const;
	bool pollEvent(sf::Event &event);
	sf::Vector2u getSize() const;
	sf::RenderWindow *getWindow() const;
	void setView(sf::Vector2f pos, sf::Vector2f size);
	OtterEngine::View *getView();
	void setDefaultView();
private:
	WindowManager();
private:
	sf::RenderWindow *_window;
	OtterEngine::View *_view;
};
