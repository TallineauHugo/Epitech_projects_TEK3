#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <functional>

#include "TextSprite.hpp"
#include "FixedSprite.hpp"
#include "MenuElement.hpp"

#pragma once

namespace OtterEngine {
	class Button : public MenuElement {
	public:
		typedef std::function<void(void*)> Callback;

		enum State {
			NORMAL,
			HOVERED,
			CLICKED
		};

		Button(std::string text, sf::Font &font, Vector2d pos, int layer,
			Vector2d size, Callback callback, void *data,
			std::string spriteNormalPath,
			std::string spriteHoveredPath = "",
			std::string spriteClickedPath = "");

		~Button();

		void setPosition(Vector2d pos);
		void setSize(Vector2d size);
		void setFontSize(unsigned int size);
		void setText(std::string str);
		void setFont(sf::Font &font);

		Vector2d getPosition();
		Vector2d getDimensions();
		State getState();
		void setCallback(Callback callback);

		void update(sf::Event &event) override;

	private:
		State _state;
		Callback _callback;
		void *_data;
		bool _called;

		int _layer;
		TextSprite *_text;
		FixedSprite *_normalSprite;
		FixedSprite *_hoveredSprite;
		FixedSprite *_clickedSprite;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};
}