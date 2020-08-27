#include "SpritesManager.hpp"
#include "TimeManager.hpp"
#include <iostream>

OtterEngine::SpritesManager::SpritesManager()
{
}

void OtterEngine::SpritesManager::addSprite(int layer, ISprite *sprite)
{
	if (!this->spriteIsInList(sprite))
		this->_sprites[layer].push_back(sprite);
}

bool OtterEngine::SpritesManager::removeSprite(ISprite *sprite)
{
	std::map<int, std::vector<ISprite*>>::iterator layer = this->_sprites.begin();
	std::vector<ISprite*>::iterator it;

	while (layer != this->_sprites.end()) {
		it = layer->second.begin();
		while (it != layer->second.end()) {
			if (*it == sprite) {
				this->_sprites[layer->first].erase(it);
				return true;
			}
			it++;
		}
		layer++;
	}
	return false;
}

bool OtterEngine::SpritesManager::spriteIsInList(OtterEngine::ISprite *sprite)
{
	std::map<int, std::vector<ISprite*>>::iterator layer = this->_sprites.begin();
	std::vector<ISprite*>::iterator it;

	while (layer != this->_sprites.end()) {
		it = layer->second.begin();
		while (it != layer->second.end()) {
			if (*it == sprite)
				return true;
			it++;
		}
		layer++;
	}
	return false;
}

void OtterEngine::SpritesManager::refresh()
{
	std::map<int, std::vector<ISprite*>>::iterator layer = this->_sprites.begin();
	std::vector<ISprite*>::iterator it;

	int i = 0;
	while (layer != this->_sprites.end()) {
		it = layer->second.begin();
		while (it < layer->second.end()) {
			if (*it) {
				(*it)->refresh();
			}
			it++;
		}
		layer++;
	}
}

void OtterEngine::SpritesManager::clear()
{
	this->_sprites.clear();
}
