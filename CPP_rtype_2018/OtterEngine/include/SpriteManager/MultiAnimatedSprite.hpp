#pragma once

#include <map>

#include "Action.hpp"
#include "AnimatedSprite.hpp"

namespace OtterEngine {
	class MultiAnimatedSprite : public virtual ISprite {
	public:
		MultiAnimatedSprite() = default;
		~MultiAnimatedSprite() = default;

	public:
		void addAnimatedSprite(Action action, AnimatedSprite *sprite);
		void refresh() override;
		void setPosition(Vector2d pos) override;
		void setSize(Vector2d size) override;
		void setAction(Action action);

	private:
		std::map<Action, AnimatedSprite *> _animatedSprites;
		Action _currentAction = UNDEFINED;
	};
}