#include "MultiAnimatedSprite.hpp"

void OtterEngine::MultiAnimatedSprite::addAnimatedSprite(Action action, AnimatedSprite *sprite)
{
	if (this->_currentAction == UNDEFINED) {
		this->_currentAction = action;
		this->_size = sprite->getSize();
		this->_pos = sprite->getSize();
	}
	this->_animatedSprites[action] = sprite;
}

void OtterEngine::MultiAnimatedSprite::refresh()
{
	Vector2d objSize;
	Vector2d objPos = this->_obj->getPos();

	if (this->_obj->getHitbox().getType() == Hitbox::SQUARE)
		objSize = this->_obj->getHitbox().getSquareSize();
	else if (this->_obj->getHitbox().getType() == Hitbox::CIRCLE) {
		objSize = {(double)this->_obj->getHitbox().getRadius() * 2, (double)this->_obj->getHitbox().getRadius() * 2};
	}
	this->_animatedSprites[this->_currentAction]->refresh();
	this->setSize({objSize.x, objSize.y});
	this->setPosition({objPos.x, objPos.y});
}

void OtterEngine::MultiAnimatedSprite::setPosition(Vector2d pos)
{
	std::map<Action, AnimatedSprite*>::iterator it = this->_animatedSprites.begin();

	while (it != this->_animatedSprites.end()) {
		it->second->setPosition(pos);
		it++;
	}
	this->_pos = pos;
}

void OtterEngine::MultiAnimatedSprite::setSize(Vector2d size)
{
	std::map<Action, AnimatedSprite*>::iterator it = this->_animatedSprites.begin();

	while (it != this->_animatedSprites.end()) {
		it->second->setSize(size);
		it++;
	}
	this->_size = size;
}

void OtterEngine::MultiAnimatedSprite::setAction(Action action)
{
	this->_currentAction = action;
}
