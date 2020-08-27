#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "MenuElement.hpp"

namespace OtterEngine {
	class Menu {
	public:
		enum Align {
			CENTERED,
			LEFT,
			RIGHT
		};

		Menu(Vector2d pos, Vector2d size, Align align);
		~Menu();

		void addElement(MenuElement *element);
		void update(sf::Event &event);

	private:
		bool isElementInMenu(MenuElement *element);

	private:
		std::map<int, MenuElement*> _elements;
		Vector2d _pos;
		Vector2d _size;
		Align _align;
	};
}