#pragma once

#include <vector>

#include "ISprite.hpp"

namespace OtterEngine {
	class ISprite;
	class  SpritesManager {
	public:
		static SpritesManager *getInstance()
		{
			static SpritesManager instance;
			return &instance;
		}

		~SpritesManager() = default;
	public:
		void addSprite(int layer, ISprite *sprite);
		bool removeSprite(ISprite *sprite);
		bool spriteIsInList(ISprite *sprite);
		void refresh();
		void clear();
		std::vector<ISprite *> getSpriteList;
	private:
		SpritesManager();
	private:
		std::map<int, std::vector<ISprite*>> _sprites;
	};
}