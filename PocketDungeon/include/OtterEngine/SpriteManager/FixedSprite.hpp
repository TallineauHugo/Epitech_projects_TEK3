#pragma once

#include "ISprite.hpp"

namespace OtterEngine {
	class FixedSprite : public virtual ISprite {
	public:
		using ISprite::ISprite;
		virtual ~FixedSprite() = default;

	public:
		bool loadSpriteFromFile(std::string filename) override;
		bool loadSpriteFromFile(std::string filename, sf::IntRect area) override;
		bool loadSpriteFromFile(std::string filename, int rowRange, int rowMax, int line, int lineMax) override {};
		void refresh() override;
		sf::Vector2i getPosition() const override;
		void setRepeated(bool b);
		void setPosition(Vector2d pos) override;
		void setSize(Vector2d size) override;
		void setRotation(int);
		void setTextureRect(sf::IntRect rect);
		void setColor(sf::Color color);

	private:
		sf::Texture _texture;
		sf::Sprite _sprite;
	};
}
