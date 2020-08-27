#pragma once

#include "Object.hpp"
#include "define.hpp"

#include <SFML/Graphics.hpp>

namespace OtterEngine {
	class ISprite {
	public:
		explicit ISprite(Object *obj = nullptr): _obj(obj) {}
		~ISprite() = default;

		virtual void refresh() = 0;
		virtual bool loadSpriteFromFile(std::string filename) = 0;
		virtual bool loadSpriteFromFile(std::string filename, sf::IntRect area) = 0;
		virtual bool loadSpriteFromFile(std::string filename, int rowRange, int rowMax, int line, int lineMax) = 0;
		virtual sf::Vector2i getPosition() const = 0;
		virtual void setSize(Vector2d size) = 0;
		virtual void setPosition(Vector2d pos) = 0;

		Vector2d getSize() const { return this->_size; };

	protected:
		Vector2d _pos;
		Vector2d _size;
		Object *_obj;
	};
}
