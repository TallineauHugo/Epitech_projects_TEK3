#pragma once

#include "ISprite.hpp"

namespace OtterEngine {
	class TextSprite : public ISprite {
	public:
		using ISprite::ISprite;
		~TextSprite() = default;

	public:
		void setString(std::string str);
		void setFont(sf::Font font);
		sf::FloatRect getBounds() const;
		void setOrigin(sf::Vector2f origin);
		void setOrigin(float posX, float posY);
		void setColor(sf::Color color);
		void setFontSize(unsigned int size);

		void refresh() override;
		bool loadSpriteFromFile(std::string filename) override;
		bool loadSpriteFromFile(std::string filename, sf::IntRect area) override;
		bool loadSpriteFromFile(std::string filename, int rowRange, int rowMax, int line, int lineMax) override {};
		void setPosition(Vector2d pos) override;
		sf::Vector2i getPosition() const override;
		void setSize(Vector2d size) override;

	private:
		sf::Text _text;
		sf::Font _font;
	};
}