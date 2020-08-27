#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "MenuElement.hpp"

namespace OtterEngine {
	class Slider : public MenuElement {
	public:
		Slider(Vector2d pos, Vector2d size, int &data, int min, int max);
		~Slider();

		void update(sf::Event &event) override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states ) const override;
		float getFactor();

	private:
		sf::RectangleShape _slider;
		sf::RectangleShape _leftHandle;
		sf::RectangleShape _rightHandle;
		sf::RectangleShape _cursor;
		Vector2d _size;

		int &_data;
		int _min;
		int _max;
		bool _dragging;
	};
}