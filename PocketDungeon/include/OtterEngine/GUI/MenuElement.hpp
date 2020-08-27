#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "Object.hpp"

namespace OtterEngine {
	class MenuElement : public virtual sf::Drawable, public Object {
	public:
		MenuElement();
		~MenuElement() override;

		virtual void update(sf::Event &event) = 0;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		Vector2d getSize() override {return this->_size;}
		virtual Vector2d getOffset() const {return _offset;}

	protected:
		Vector2d _size = {0, 0};
		Vector2d _offset;
	};
}
