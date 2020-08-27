#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "MenuElement.hpp"
#include "ISprite.hpp"

namespace OtterEngine {
	class SpriteSlider : public virtual MenuElement {
	public:
		SpriteSlider(std::string filename, Vector2d pos, int layer,
			Vector2d size, int &data, int min, int max);
		~SpriteSlider();

		void update(sf::Event &event) override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		float getFactor();
		void updateSprites();

	private:
		ISprite *_slider;
		ISprite *_leftHandle;
		ISprite *_rightHandle;
		ISprite *_cursor;

		int &_data;
		int _min;
		int _max;
		bool _dragging;
	};
}