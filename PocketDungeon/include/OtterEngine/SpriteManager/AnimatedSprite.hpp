#pragma once

#include <map>

#include "FixedSprite.hpp"

namespace OtterEngine {
	class AnimatedSprite : public virtual ISprite {
	public:
		using ISprite::ISprite;
		~AnimatedSprite();

	public:
		bool loadSpriteFromFile(std::string filename) override;
		bool loadSpriteFromFile(std::string filename, sf::IntRect area) override;
		bool loadSpriteFromFile(std::string filename, int rowRange, int rowMax, int line, int lineMax) override;
		void refresh() override;
		void setPosition(Vector2d pos) override;
		sf::Vector2i getPosition() const override;
		void setSize(Vector2d size) override;
		void setSpeed(int speed);

	private:
		std::map<int, FixedSprite *> _sprites;
		int _nbFrame;
		int _currentFrame;
		float _waitedTime;
		float _speed;
	};
}