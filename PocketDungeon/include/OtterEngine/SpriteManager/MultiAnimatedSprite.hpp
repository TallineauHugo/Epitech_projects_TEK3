#pragma once

#include <map>

#include "Action.hpp"
#include "AnimatedSprite.hpp"

namespace OtterEngine {
	class MultiAnimatedSprite : public virtual ISprite {
	public:
		using ISprite::ISprite;
		~MultiAnimatedSprite() = default;

	public:
		void addAnimatedSprite(Action action, AnimatedSprite *sprite);
		void refresh() override;
		void setPosition(Vector2d pos) override;
		void setSize(Vector2d size) override;
		void setAction(Action action);
		bool loadSpriteFromFile(std::string filename) override;
		bool loadSpriteFromFile(std::string filename, sf::IntRect area) override;
		bool loadSpriteFromFile(std::string filename, int rowRange, int rowMax, int line, int lineMax) override;
		sf::Vector2i getPosition() const override;

	private:
		std::map<Action, AnimatedSprite *> _animatedSprites;
		Action _currentAction = UNDEFINED;
	};
}
