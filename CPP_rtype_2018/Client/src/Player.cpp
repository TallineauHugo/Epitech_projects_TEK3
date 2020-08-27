#include "Player.hpp"
#include <iostream>
#include "Bullet.hpp"
#include "Bomb.hpp"
#include "Energy.hpp"
#include "InputManager.hpp"
#include "Id.hpp"
#include "AnimatedSprite.hpp"
#include "WindowManager.hpp"

/*std::size_t Player::getId() const
{
	return _id;
}*/

Player::Player(Vector2d pos, std::size_t id) : 
Object(id), SpaceShip(pos, 0.5, ALLY, id), _energy(0), _shoot(false), _bomb(false)
{
	static bool first = true;

	std::cout << "NEW PLAYER" << std::endl;
	_name += "Player::";
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::RightReaction, &Player::RightVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::UpReaction, &Player::UpVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::DownReaction, &Player::DownVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Shoot", &Player::ShootReaction, &Player::ShootVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("CollideEnergy", &Player::CollideEnergyReaction, &Player::CollideEnergyVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("CollideEnnemy", &Player::CollideEnnemyReaction, &Player::CollideEnnemyVerification));
    	addEvent<Player>(_events, OtterEngine::Event<Player>("Bomb", &Player::hasEnergyReaction, &Player::hasEnergyVerification));
	_dir[UP] = false;
	_dir[RIGHT] = false;
	_dir[DOWN] = false;
	_dir[LEFT] = false;
	_sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/spaceship.png", 9, 9, 1, 1);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
	if (first) {
		_gauge = new OtterEngine::Gauge("ressources/texture/gauge.png", {200, (double)WindowManager::getInstance()->getSize().y - 50}, 2, {300, 100}, _energy, 0, 500);
		first = false;
	}
	else
		_gauge = NULL;
}

Player::~Player()
{

}

void Player::StartMoveUp()
{
	_dir[UP] = true;
}

void Player::StartMoveRight()
{
	_dir[RIGHT] = true;
}

void Player::StartMoveDown()
{
	_dir[DOWN] = true;
}

void Player::StartMoveLeft()
{
	_dir[LEFT] = true;
}

void Player::StopMoveUp()
{
	_dir[UP] = false;
}

void Player::StopMoveRight()
{
	_dir[RIGHT] = false;
}

void Player::StopMoveDown()
{
	_dir[DOWN] = false;
}

void Player::StopMoveLeft()
{
	_dir[LEFT] = false;
}

void Player::StartShoot()
{
	_shoot = true;
}

void Player::StopShoot()
{
	_shoot = false;
}

void Player::StartBomb()
{
	_bomb = true;
}

void Player::StopBomb()
{
	_bomb = false;
}

bool Player::ShootVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return _shoot;
}

int Player::ShootReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	return shootBullet(oe);
}

bool Player::LeftVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return _dir[LEFT];
}

bool Player::NoLeftVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !_dir[LEFT];
}

bool Player::UpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return _dir[UP];
}

bool Player::NoUpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !_dir[UP];
}

bool Player::RightVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return _dir[RIGHT];
}

bool Player::NoRightVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !_dir[RIGHT];
}

bool Player::DownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return _dir[DOWN];
}

bool Player::NoDownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !_dir[DOWN];
}

int Player::LeftReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.x = -500;
	removeEvent(_events, "Left");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::NoLeftReaction, &Player::NoLeftVerification));
	return 0;
}

int Player::NoLeftReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	if (_velocity.x == -500)
		_velocity.x = 0;
	removeEvent(_events, "Left");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
	return 0;
}

int Player::UpReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.y = -500;
	removeEvent(_events, "Up");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::NoUpReaction, &Player::NoUpVerification));
	return 0;
}

int Player::NoUpReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	if (_velocity.y == -500)
		_velocity.y = 0;
	removeEvent(_events, "Up");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::UpReaction, &Player::UpVerification));
	return 0;
}

int Player::RightReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.x = 500;
	removeEvent(_events, "Right");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::NoRightReaction, &Player::NoRightVerification));
	return 0;
}

int Player::NoRightReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	if (_velocity.x == 500)
		_velocity.x = 0;
	removeEvent(_events, "Right");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::RightReaction, &Player::RightVerification));
	return 0;
}

int Player::DownReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.y = 500;
	removeEvent(_events, "Down");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::NoDownReaction, &Player::NoDownVerification));
	return 0;
}

int Player::NoDownReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	if (_velocity.y == 500)
		_velocity.y = 0;
	removeEvent(_events, "Down");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::DownReaction, &Player::DownVerification));
	return 0;
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
	return 0;
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
			_energy += dynamic_cast<Energy *>(objs[it->first])->getValue();
			if (_energy > 500)
				_energy = 500;
			OtterEngine::SpritesManager::getInstance()->removeSprite(objs[it->first]->getSprite());
			oe->removeObject(it->first);
		}
	}
	return 0;
}

bool Player::hasEnergyVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (_energy == 500)
		return true;
	return false;
}

int Player::hasEnergyReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	removeEvent(_events, "Bomb");
    addEvent<Player>(_events, OtterEngine::Event<Player>("Bomb", &Player::BombShootReaction, &Player::BombShootVerification));
    return 0;
}

bool Player::BombShootVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return _bomb;
}

int Player::BombShootReaction(OtterEngine::Engine *oe)
{
	_energy = 0;
	std::cout << "launching bomb\n\n";
	removeEvent(_events, "Bomb");
	oe->addObject(new Bomb(_hitbox.getPos(), Vector2d(2000, 0), _camp, Id::getInstance()->getNextId()));
        addEvent<Player>(_events, OtterEngine::Event<Player>("Bomb", &Player::hasEnergyReaction, &Player::hasEnergyVerification));
    return 0;
}

void Player::updateEvents(OtterEngine::Engine *oe)
{
	if (this->_gauge)
		this->_gauge->update();
	for (std::size_t i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
