#include "Player.hpp"
#include "WindowManager.hpp"
#include <iostream>
#include "Bullet.hpp"
#include "Bomb.hpp"
#include "Energy.hpp"
#include "InputManager.hpp"
#include "AnimatedSprite.hpp"

Player::Player(Vector2d pos) : SpaceShip(pos, 0.5, ALLY)
{
	_velocity.x = 100;
	_name += "Player::";
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::RightReaction, &Player::RightVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::UpReaction, &Player::UpVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::DownReaction, &Player::DownVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Shoot", &Player::ShootReaction, &Player::ShootVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("CollideEnergy", &Player::CollideEnergyReaction, &Player::CollideEnergyVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("CollideEnnemy", &Player::CollideEnnemyReaction, &Player::CollideEnnemyVerification));
        addEvent<Player>(_events, OtterEngine::Event<Player>("Bomb", &Player::hasEnergyReaction, &Player::hasEnergyVerification));
        addEvent<Player>(_events, OtterEngine::Event<Player>("CollideCooldown", &Player::CollideCooldownReducReaction, &Player::CollideCooldownReducVerification));
    _sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/Wall.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
}

Player::~Player()
{

}

bool Player::ShootVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Space);
}

int Player::ShootReaction(OtterEngine::Engine *oe)
{
	return shootBullet(oe);
}

bool Player::LeftVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Left);
}

bool Player::NoLeftVerification(OtterEngine::Engine *oe)
{
	return (!InputManager::getInstance()->isKeyPressed(sf::Keyboard::Left)
		|| WindowManager::getInstance()->getView()->getPosition().x - WindowManager::getInstance()->getView()->getSize().x / 2 > getPos().x - 40);
}

bool Player::UpVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Up);
}

bool Player::NoUpVerification(OtterEngine::Engine *oe)
{
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Up);	
}

bool Player::RightVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Right);
}

bool Player::NoRightVerification(OtterEngine::Engine *oe)
{
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Right);	
}

bool Player::DownVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Down);
}

bool Player::NoDownVerification(OtterEngine::Engine *oe)
{
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Down);
}

bool Player::ScrollerVerification(OtterEngine::Engine *oe)
{
	return (WindowManager::getInstance()->getView()->getPosition().x - WindowManager::getInstance()->getView()->getSize().x / 2 < getPos().x - 40);
}

int Player::ScrollerReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "Left");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
}

int Player::LeftReaction(OtterEngine::Engine *oe)
{
	_velocity.x = -400;
	removeEvent(_events, "Left");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::NoLeftReaction, &Player::NoLeftVerification));
}

int Player::NoLeftReaction(OtterEngine::Engine *oe)
{
	if (_velocity.x == -400)
		_velocity.x = 100;
	removeEvent(_events, "Left");
	if (WindowManager::getInstance()->getView()->getPosition().x - WindowManager::getInstance()->getView()->getSize().x  / 2 > getPos().x - 40)
		addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::ScrollerReaction, &Player::ScrollerVerification));
	else
		addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
}

int Player::UpReaction(OtterEngine::Engine *oe)
{
	_velocity.y = -500;
	removeEvent(_events, "Up");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::NoUpReaction, &Player::NoUpVerification));
}

int Player::NoUpReaction(OtterEngine::Engine *oe)
{
	if (_velocity.y == -500)
		_velocity.y = 0;
	removeEvent(_events, "Up");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::UpReaction, &Player::UpVerification));
}

int Player::RightReaction(OtterEngine::Engine *oe)
{
	_velocity.x = 500;
	removeEvent(_events, "Right");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::NoRightReaction, &Player::NoRightVerification));
}

int Player::NoRightReaction(OtterEngine::Engine *oe)
{
	if (_velocity.x == 500)
		_velocity.x = 100;
	removeEvent(_events, "Right");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::RightReaction, &Player::RightVerification));
}

int Player::DownReaction(OtterEngine::Engine *oe)
{
	_velocity.y = 500;
	removeEvent(_events, "Down");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::NoDownReaction, &Player::NoDownVerification));
}

int Player::NoDownReaction(OtterEngine::Engine *oe)
{
	if (_velocity.y == 500)
		_velocity.y = 0;
	removeEvent(_events, "Down");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::DownReaction, &Player::DownVerification));
}


bool Player::CollideEnnemyVerification(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();
	
	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if ((it->first == i && ((objs[it->second]->getName().find("Bullet") != std::string::npos && dynamic_cast<Bullet *>(objs[it->second])->getCamp() == ENNEMY)
					|| (objs[it->second]->getName().find("SpaceShip") != std::string::npos && dynamic_cast<SpaceShip *>(objs[it->second])->getCamp() == ENNEMY)))
		    || (it->second == i && ((objs[it->first]->getName().find("Bullet") != std::string::npos && dynamic_cast<Bullet *>(objs[it->first])->getCamp() == ENNEMY)
					    || (objs[it->first]->getName().find("SpaceShip") != std::string::npos && dynamic_cast<SpaceShip *>(objs[it->first])->getCamp() == ENNEMY))))
		{
			if (objs[it->second]->getName().find("Bullet") != std::string::npos)
				dynamic_cast<Bullet *>(objs[it->second])->hit(oe);
			else if(objs[it->first]->getName().find("Bullet") != std::string::npos)
				dynamic_cast<Bullet *>(objs[it->first])->hit(oe);
			return true;
		}
	}
	return false;
}

int Player::CollideEnnemyReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

bool Player::CollideEnergyVerification(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();
	
	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if (it->first == i && objs[it->second]->getName().find("Energy") != std::string::npos)
			return true;
		else if (it->second == i && objs[it->first]->getName().find("Energy") != std::string::npos)
			return true;
	}
	return false;
}

int Player::CollideEnergyReaction(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	
	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if (it->first == i && objs[it->second]->getName().find("Energy") != std::string::npos) {
			_energy += dynamic_cast<Energy *>(objs[it->second])->getValue();
			if (_energy > 500)
				_energy = 500;
			OtterEngine::SpritesManager::getInstance()->removeSprite(objs[it->second]->getSprite());
			oe->removeObject(it->second);
		}
		else if (it->second == i && objs[it->first]->getName().find("Energy") != std::string::npos)
		{
			_energy+= dynamic_cast<Energy *>(objs[it->first])->getValue();
			if (_energy > 500)
				_energy = 500;
			OtterEngine::SpritesManager::getInstance()->removeSprite(objs[it->first]->getSprite());
			oe->removeObject(it->first);
		}
	}
}

bool Player::CollideCooldownReducVerification(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if (it->first == i && objs[it->second]->getName().find("CooldownReduc") != std::string::npos)
			return true;
		else if (it->second == i && objs[it->first]->getName().find("CooldownReduc") != std::string::npos)
			return true;
	}
	return false;
}

int Player::CollideCooldownReducReaction(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();


	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if (it->first == i && objs[it->second]->getName().find("CooldownReduc") != std::string::npos) {
			_cooldown -= 0.2;
			if (_cooldown < 0.1)
				_cooldown = 0.1;
			OtterEngine::SpritesManager::getInstance()->removeSprite(objs[it->second]->getSprite());
			oe->removeObject(it->second);
		}
		else if (it->second == i && objs[it->first]->getName().find("CooldownReduc") != std::string::npos)
		{
			_cooldown -= 0.2;
			if (_cooldown < 0.1)
				_cooldown = 0.1;
			OtterEngine::SpritesManager::getInstance()->removeSprite(objs[it->first]->getSprite());
			oe->removeObject(it->first);
		}
	}
}


bool Player::hasEnergyVerification(OtterEngine::Engine *oe)
{
	if (_energy == 500)
		return true;
	return false;
}

int Player::hasEnergyReaction(OtterEngine::Engine *oe)
{
	removeEvent(_events, "Bomb");
        addEvent<Player>(_events, OtterEngine::Event<Player>("Bomb", &Player::BombShootReaction, &Player::BombShootVerification));
}

bool Player::BombShootVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::B);
}

int Player::BombShootReaction(OtterEngine::Engine *oe)
{
	_energy = 0;
	std::cout << "launching bomb\n\n";
	removeEvent(_events, "Bomb");
	oe->addObject(new Bomb(_hitbox.getPos(), Vector2d(2000, 0), _camp));
        addEvent<Player>(_events, OtterEngine::Event<Player>("Bomb", &Player::hasEnergyReaction, &Player::hasEnergyVerification));
}

void Player::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
