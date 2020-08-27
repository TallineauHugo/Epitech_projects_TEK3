//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// attack
//

#include <iostream>

#include "Attack.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"
#include "Event.hpp"
#include "Pokemon.hpp"
#include "TextSprite.hpp"
#include "Player.hpp"

Attack::Attack(Attack *atk, Vector2d velocity, Vector2d pos)
	: Object(),_atkName(atk->getAtkName()), _power(atk->getPower()), _hit(atk->getHit()), _critRate(atk->getCritRate()), _type(atk->getType()), _element(atk->getElement()), _host(atk->getHost()), _range(atk->getRange())
{
	// _velocity = velocity;
	// _aim.x = pos.x + (velocity.x / 1); //4
	// _aim.y = pos.y + (velocity.y / 1); //4
	// _hitbox.setPos(pos);
	// _hitbox.setType(OtterEngine::Hitbox::SQUARE);
	// _hitbox.setSquareSize(Vector2d(20, 20));
	// _sprite = new OtterEngine::FixedSprite(this);
	// _sprite->loadSpriteFromFile("ressources/texture/Wall.png");
	// OtterEngine::SpritesManager::getInstance()->addSprite(2, _sprite);
	// addEvent<Attack>(_events, OtterEngine::Event<Attack>("Fade", &Attack::fadeReaction, &Attack::fadeVerification));
	// addEvent<Attack>(_events, OtterEngine::Event<Attack>("Collide", &Attack::collideReaction, &Attack::collideVerification));
}

Attack::Attack(std::string name, std::size_t dmg, std::size_t hit, float critRate, DamageType type, Types element, Pokemon *host, float range)
	: _atkName(name), _power(dmg), _hit(hit), _critRate(critRate), _type(type), _element(element), _host(host), _range(range), _oldVelo({0, 0})
{

}

void Attack::setHost(Pokemon *pkmn)
{
	_host = pkmn;
}

Attack *Attack::clone(Attack *atk, Vector2d velocity, Vector2d pos)
{
	return new Attack(atk, velocity, pos);
}

Attack::~Attack()
{

}

void Attack::show()
{
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
}

void Attack::hide()
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
}

std::string Attack::getAtkName() const
{
	return _atkName;
}

std::size_t Attack::getPower() const
{
	return _power;
}

std::size_t Attack::getHit() const
{
	return _hit;
}

float Attack::getCritRate() const
{
	return _critRate;
}

DamageType Attack::getType() const
{
	return _type;
}

Types Attack::getElement() const
{
	return _element;
}

Pokemon *Attack::getHost() const
{
	return _host;
}

float Attack::getRange() const
{
	return _range;
}

bool Attack::collideVerification(OtterEngine::Engine *oe)
{
	std::size_t i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	/*Test*/
	// sf::Font font;
	// std::string str = "-" + std::to_string(_power);
	// font.loadFromFile("ressources/font/arial.ttf");
	// OtterEngine::TextSprite *text = new OtterEngine::TextSprite;
	// text->setFont(font);
	// text->setColor(sf::Color::Red);
	// text->setString(str);
	// text->setFontSize(30);
	// text->setStyle(sf::Text::Bold);


	for (std::map<int, int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it) {
		if (it->first == i && dynamic_cast<Pokemon *>(objs[it->second]) != nullptr && objs[it->second] != _host) {
			if (dynamic_cast<Pokemon *>(objs[it->second])->takeDamage(*this) == false) {
				//dynamic_cast<Pokemon *>(objs[it->second])->hide();
				//oe->removeObject(oe->getIndex(objs[it->second]));
			}
			// text->setPosition({objs[it->second]->getPos().x + 5, objs[it->second]->getPos().y - 15});
			// OtterEngine::SpritesManager::getInstance()->addSprite(1, text);
			return true;
		}
		else if (it->second == i && dynamic_cast<Pokemon *>(objs[it->first]) != nullptr && objs[it->first] != _host) {
			if (dynamic_cast<Pokemon *>(objs[it->first])->takeDamage(*this) == false) {
				//dynamic_cast<Pokemon *>(objs[it->first])->hide();
				//oe->removeObject(oe->getIndex(objs[it->first]));
			}

			// text->setPosition({objs[it->first]->getPos().x + 5, objs[it->first]->getPos().y - 15});
			// OtterEngine::SpritesManager::getInstance()->addSprite(1, text);
			return true;
		}
		else if (it->first == i && objs[it->second]->getName().find("Player") != std::string::npos && dynamic_cast<Player *>(objs[it->second])->GetCurrentPokemon() != _host) {
			if (dynamic_cast<Player *>(objs[it->second])->GetCurrentPokemon()->takeDamage(*this) == false) {
				//dynamic_cast<Player *>(objs[it->second])->GetCurrentPokemon()->hide();
				// oe->removeObject(oe->getIndex(dynamic_cast<Player *>(objs[it->second])->GetCurrentPokemon()));
			}
			return true;
		}
		else if (it->second == i && objs[it->first]->getName().find("Player") != std::string::npos && dynamic_cast<Player *>(objs[it->first])->GetCurrentPokemon() != _host) {
			if (dynamic_cast<Player *>(objs[it->first])->GetCurrentPokemon()->takeDamage(*this) == false) {
				//dynamic_cast<Player *>(objs[it->first])->GetCurrentPokemon()->hide();
				// oe->removeObject(oe->getIndex(dynamic_cast<Player *>(objs[it->first])->GetCurrentPokemon()));
			}
			return true;
		}
	}
	return false;
}

int Attack::collideReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

bool Attack::fadeVerification(OtterEngine::Engine *oe)
{
	Vector2d pos = this->getPos();

	if (((_velocity.x < 0 && pos.x <= _aim.x) ||
	     (_velocity.x > 0 && pos.x >= _aim.x)) &&
	    ((_velocity.y < 0 && pos.y <= _aim.y) ||
	     (_velocity.y > 0 && pos.y >= _aim.y)))
		return true;
	return false;
}

int Attack::fadeReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void Attack::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
