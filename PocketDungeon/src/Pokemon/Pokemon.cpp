//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon
//

#include <iostream>
#include "Pokemon.hpp"
#include "TypeTable.hpp"
#include "AtkManager.hpp"
#include "Tackle.hpp"
#include "ThunderShock.hpp"
#include "Growl.hpp"
#include "Hitbox.hpp"
#include "FixedSprite.hpp"
#include "AnimatedSprite.hpp"
#include "MultiAnimatedSprite.hpp"
#include "SpritesManager.hpp"
#include "TimeManager.hpp"
#include "InputManager.hpp"
#include "VineWhip.h"
#include "PokemonLoader.hpp"
#include "Gauge.hpp"
#include "ItemFactory.hpp"

Pokemon::Pokemon(Pokemon *pkmn)
	: Object(), _name(pkmn->getName()), _nickname(pkmn->getNickname()), _evOnDeath("+0hp"), _id(pkmn->getId()), _captureRate(pkmn->getCaptureRate()), 
	_inertness(false), _attacking(false), _facing(DOWN), _angleShot(0), _hpGauge(nullptr), _expGauge(nullptr)
{
	Object::_name += "PKMN::";
	std::cout << "\nOn génère " << _name << std::endl;
	setIv(HP, rand() % 32);
	setIv(ATK, rand() % 32);
	setIv(DEF, rand() % 32);
	setIv(ATKSPE, rand() % 32);
	setIv(DEFSPE, rand() % 32);
	setIv(SPEED, rand() % 32);

	_evOnDeath = "+" + std::to_string(pkmn->getEvOnDeath().second) + pkmn->getEvOnDeath().first;

	_stats.setHost(this);
	_stats.setExpOnDeath(pkmn->getExpOnDeath());
	this->_stats.setType(pkmn);
	this->_stats.setEvolution(std::to_string(pkmn->getEvolution().first) + "-" + pkmn->getEvolution().second);

	_stats.setBaseStat(std::pair<std::string, std::string>(HP, std::to_string(pkmn->getBaseStat(HP))));
	_stats.setBaseStat(std::pair<std::string, std::string>(ATK, std::to_string(pkmn->getBaseStat(ATK))));
	_stats.setBaseStat(std::pair<std::string, std::string>(DEF, std::to_string(pkmn->getBaseStat(DEF))));
	_stats.setBaseStat(std::pair<std::string, std::string>(ATKSPE, std::to_string(pkmn->getBaseStat(ATKSPE))));
	_stats.setBaseStat(std::pair<std::string, std::string>(DEFSPE, std::to_string(pkmn->getBaseStat(DEFSPE))));
	_stats.setBaseStat(std::pair<std::string, std::string>(SPEED, std::to_string(pkmn->getBaseStat(SPEED))));

	_atk.setHost(this);
	_atk.setMovepool(pkmn->getMovepool());
	_atk.updateMoves(_stats.getLvl());

	//if (!_name.compare("pikachu")) {
		_sprite = new OtterEngine::MultiAnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteUp = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteRight = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteDown = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteLeft = new OtterEngine::AnimatedSprite(this);

		OtterEngine::AnimatedSprite *spriteIdleUp = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteIdleRight = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteIdleDown = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteIdleLeft = new OtterEngine::AnimatedSprite(this);
		
		spriteDown->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 1, 8);
		spriteUp->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 2, 8);
		spriteLeft->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 3, 8);
		spriteRight->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 4, 8);

		spriteIdleDown->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 5, 8);
		spriteIdleUp->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 6, 8);
		spriteIdleLeft->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 7, 8);
		spriteIdleRight->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 8, 8);

		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_UP, spriteUp);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_RIGHT, spriteRight);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_DOWN, spriteDown);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_LEFT, spriteLeft);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_UP, spriteIdleUp);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_RIGHT, spriteIdleRight);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_DOWN, spriteIdleDown);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_LEFT, spriteIdleLeft);
		
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->setAction(IDLE_DOWN);
		addEvent<Pokemon>(_events, OtterEngine::Event<Pokemon>("Always", &Pokemon::updateSprite, &Pokemon::always));
	/*}
	else {
		_sprite = new OtterEngine::FixedSprite(this);
		_sprite->loadSpriteFromFile("ressources/" + _name + ".png");
	}*/
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setPos(Vector2d(100, 100));
	_hitbox.setSquareSize(Vector2d(70, 70));

	//this->setInertness(true);
	addEvent<Pokemon>(_events, OtterEngine::Event<Pokemon>("Update", &Pokemon::UpdateReaction, &Pokemon::UpdateVerification));

	_hpGauge = new OtterEngine::Gauge("ressources/texture/hp_bar.png", "ressources/texture/hp_bar_fill.png", getPos(), 3, Vector2d(137, 22), (int&)_stats.getrefCurrentHp(), 0, (int&)_stats.getrefMaxHp());
	_expGauge = new OtterEngine::Gauge("ressources/texture/xp_bar.png", "ressources/texture/xp_bar_fill.png", getPos(), 3, Vector2d(137, 22), (int&)_stats.getrefCurrentExp(), 0, (int&)_stats.getrefNextLvlExp());
}

Pokemon::Pokemon(std::string name)
	: _name(name), _nickname(name), _evOnDeath("+0hp"), _id(0), _captureRate(0), _facing(RIGHT), _hpGauge(nullptr), _expGauge(nullptr)
{
	Object::_name += "PKMN_TEMPLATE::";
}

Pokemon::~Pokemon()
{
	std::cout << "destroy " << _name << " (a.k.a " << Object::_name << ")" << std::endl;
	this->hide();
	if (_hpGauge)
		delete _hpGauge;
	if (_expGauge)
		delete _expGauge;
}

void Pokemon::update(float deltaTime)
{
	_stats.update(deltaTime);

	if (_hpGauge) {
		Vector2d pos = getPos();

		if (pos.y >= 50)
			pos.y -= 50;
		
		_hpGauge->setPos(pos);
		_hpGauge->update();
	}

	if (_expGauge) {
		Vector2d pos = getPos();

		if (pos.y >= 50)
			pos.y -= 50;
		
		_expGauge->setPos(pos);
		_expGauge->update();
	}
}

void Pokemon::evolve()
{
	std::cout << "try evolve ...";
	Pokemon *evo = PokemonLoader::getInstance()->getPokemonByName(_stats.getEvolve());

	if (!evo) {
		std::cout << "Can't load evolution" << _stats.getEvolve() << std::endl;
		return;
	}
	this->_name = _stats.getEvolve();
	this->setId(evo->getId());
	this->_stats.setType(evo);
	this->_evOnDeath = "+" + std::to_string(evo->getEvOnDeath().second) + evo->getEvOnDeath().first;
	this->_stats.setExpOnDeath(evo->getExpOnDeath());
	this->_captureRate = evo->getCaptureRate();
	this->setBaseStat(std::make_pair(HP, std::to_string(evo->getBaseStat(HP))));
	this->setBaseStat(std::make_pair(ATK, std::to_string(evo->getBaseStat(ATK))));
	this->setBaseStat(std::make_pair(DEF, std::to_string(evo->getBaseStat(DEF))));
	this->setBaseStat(std::make_pair(ATKSPE, std::to_string(evo->getBaseStat(ATKSPE))));
	this->setBaseStat(std::make_pair(DEFSPE, std::to_string(evo->getBaseStat(DEFSPE))));
	this->setBaseStat(std::make_pair(SPEED, std::to_string(evo->getBaseStat(SPEED))));
	this->_atk.setMovepool(evo->getMovepool());
	this->_stats.setEvolution(std::to_string(evo->getEvolution().first) + "-" + evo->getEvolution().second);

	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);

	if (!_name.compare("pikachu")) {
		_sprite = new OtterEngine::MultiAnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteUp = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteRight = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteDown = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteLeft = new OtterEngine::AnimatedSprite(this);

		OtterEngine::AnimatedSprite *spriteIdleUp = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteIdleRight = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteIdleDown = new OtterEngine::AnimatedSprite(this);
		OtterEngine::AnimatedSprite *spriteIdleLeft = new OtterEngine::AnimatedSprite(this);
		
		spriteDown->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 1, 8);
		spriteUp->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 2, 8);
		spriteLeft->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 3, 8);
		spriteRight->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 3, 3, 4, 8);

		spriteIdleDown->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 5, 8);
		spriteIdleUp->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 6, 8);
		spriteIdleLeft->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 7, 8);
		spriteIdleRight->loadSpriteFromFile("ressources/animatedSprites/" + _name + ".png", 1, 3, 8, 8);

		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_UP, spriteUp);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_RIGHT, spriteRight);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_DOWN, spriteDown);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(RUN_LEFT, spriteLeft);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_UP, spriteIdleUp);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_RIGHT, spriteIdleRight);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_DOWN, spriteIdleDown);
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->addAnimatedSprite(IDLE_LEFT, spriteIdleLeft);
		
		(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->setAction(IDLE_DOWN);
		addEvent<Pokemon>(_events, OtterEngine::Event<Pokemon>("Always", &Pokemon::updateSprite, &Pokemon::always));
	}
	else {
		_sprite = new OtterEngine::FixedSprite(this);
		_sprite->loadSpriteFromFile("ressources/" + _name + ".png");
	}

	OtterEngine::SpritesManager::getInstance()->addSprite(3, _sprite);
	std::cout << "done !\n";
}

bool Pokemon::haveStatus(Status::Status status) const
{
	return _stats.haveStatus(status);
}

bool Pokemon::takeDamage(Attack atk)
{
	std::cout << std::endl << this->getName() << " takes damage from " << atk.getName() << " by " << atk.getHost()->getName() << std::endl;
	_stats.takeDamage(atk);

	if (this->isAlive()) {
		std::cout << this->getName() << ": " << this->getCurrentHp() << "/" << this->getMaxHp() << " HP" << std::endl;
		return true;
	}

	std::cout << this->getName() << " dies and give " << std::to_string(_stats.getExpOnDeath()) << " exp to " << atk.getHost()->getName() << std::endl;
	atk.getHost()->gainExp(_stats.getExpOnDeath());
	atk.getHost()->gainEv(this->getEvOnDeath());
	addEvent<Pokemon>(_events, OtterEngine::Event<Pokemon>("Die", &Pokemon::die, &Pokemon::isDead));
	return false;
}

int Pokemon::getFacing() const
{
	return _facing;
}

void Pokemon::setFacing(int facing)
{
	_facing = facing;
}

bool Pokemon::applyStatusFor(Status::Status status, float seconds)
{
	return _stats.applyStatusFor(status, seconds);
}

bool Pokemon::canMove() const //à modifier
{
	return _stats.canMove();
}

void Pokemon::lvlUp()
{
	_stats.lvlUp();
}

void Pokemon::gainExp(std::size_t amount)
{
	std::cout << this->getName() << " gain " << amount << " exp !" << std::endl;
	_stats.gainExp(amount);
}

void Pokemon::gainEv(std::pair<std::string, std::size_t> ev)
{
	_stats.gainEv(ev.first, ev.second);
}

void Pokemon::heal(std::size_t amount)
{
	_stats.heal(amount);
}

void Pokemon::fullHeal()
{
	_stats.heal(_stats.getMaxHp() - _stats.getCurrentHp());
}

void Pokemon::show()
{
	OtterEngine::SpritesManager::getInstance()->addSprite(3, _sprite);
	if (_hpGauge)
		_hpGauge->show();
	if (_expGauge)
		_expGauge->show();
}

void Pokemon::hideHpBar()
{
	if (_hpGauge)
		_hpGauge->hide();
	if (_expGauge)
		_expGauge->hide();
}

void Pokemon::hide()
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	this->hideHpBar();
}

void Pokemon::updateMoves()
{
	_atk.updateMoves(_stats.getLvl());
}

std::size_t Pokemon::getBaseStat(const std::string stat) const
{
	return _stats.getBaseStat(stat);
}

bool Pokemon::isAlive() const
{
	return _stats.getCurrentHp() > 0;
}

//getters and setters

bool Pokemon::always(OtterEngine::Engine *oe)
{
	return true;
}

int Pokemon::updateSprite(OtterEngine::Engine *oe)
{
	Action action;

	if (_velocity.x == 0 && _velocity.y == 0) {
		switch (_facing) {
			case UP:
				action = IDLE_UP;
				break;
			case RIGHT:
				action = IDLE_RIGHT;
				break;
			case DOWN:
				action = IDLE_DOWN;
				break;
			case LEFT:
				action = IDLE_LEFT;
				break;
		}
	}
	else {	
		switch (_facing) {
			case UP:
				action = RUN_UP;
				break;
			case RIGHT:
				action = RUN_RIGHT;
				break;
			case DOWN:
				action = RUN_DOWN;
				break;
			case LEFT:
				action = RUN_LEFT;
				break;
		}
	}
	(dynamic_cast<OtterEngine::MultiAnimatedSprite *>(_sprite))->setAction(action);
}

void Pokemon::setPos(Vector2d pos)
{
	_hitbox.setPos(pos);
}

void Pokemon::setBaseStat(std::pair<std::string, std::string> stat)
{
	if (stat.first == ID)
		this->setId(std::stoi(stat.second));
	else if (stat.first == TYPE)
		_stats.setType(stat.second);
	else if (stat.first == EV)
		_evOnDeath = stat.second;
	else if (stat.first == EXP)
		_stats.setExpOnDeath(std::stoi(stat.second));
	else if (stat.first == RATE)
		_captureRate = std::stoi(stat.second);
	else if (stat.first == MOVEPOOL)
		_atk.setMovepool(stat.second);
	else if (stat.first == EVOLVE)
		_stats.setEvolution(stat.second);
	else
		_stats.setBaseStat(stat);
}

AtkManager Pokemon::getAtkManager()const
{
	return _atk;
}


void Pokemon::setId(std::size_t id)
{
	_id = id;
}

void Pokemon::setIv(std::string stat, std::size_t value)
{
	if (stat == HP ||
		stat == ATK ||
		stat == DEF ||
		stat == ATKSPE ||
		stat == DEFSPE ||
		stat == SPEED)
		_stats.setIv(stat, value);
}

void Pokemon::setLvl(std::size_t lvl)
{
	while (_stats.getLvl() != lvl) {
		this->lvlUp();
		_atk.updateMoves(_stats.getLvl());
	}
	_stats.updateStats();
}

void Pokemon::setNickname(std::string nickname)
{
	_nickname = nickname;
}

Vector2d Pokemon::getPos()
{
	return _hitbox.getPos();
}

std::size_t Pokemon::getMaxHp() const
{
	return _stats.getMaxHp();
}

std::size_t Pokemon::getCurrentHp() const
{
	return _stats.getCurrentHp();
}

std::size_t Pokemon::getAtk() const
{
	return _stats.getStat(ATK);
}

std::size_t Pokemon::getDef() const
{
	return _stats.getStat(DEF);
}

std::size_t Pokemon::getAtkSpe() const
{
	return _stats.getStat(ATKSPE);
}

std::size_t Pokemon::getDefSpe() const
{
	return _stats.getStat(DEFSPE);
}

std::size_t Pokemon::getSpeed() const
{
	return _stats.getStat(SPEED);
}

std::size_t Pokemon::getIv(std::string iv) const
{
	return _stats.getIv(iv);
}

std::size_t Pokemon::getId() const
{
	return _id;
}

std::size_t Pokemon::getLvl() const
{
	return _stats.getLvl();
}

std::size_t Pokemon::getCaptureRate() const
{
	return _captureRate;
}

std::size_t Pokemon::getExpOnDeath() const
{
	return _stats.getExpOnDeath();
}

std::pair<std::string, std::size_t> Pokemon::getEvOnDeath() const
{
	std::string stat;
	std::string tmp;
	std::size_t nb;
	std::size_t pos;

	pos = _evOnDeath.find('+');
	if (pos != std::string::npos) {
		tmp = _evOnDeath.substr(pos + 1, 1);
		nb = std::stoi(tmp);
		stat = _evOnDeath.substr(pos + 2, std::string::npos);
		return std::make_pair(stat, nb);
	}
	return std::make_pair(HP, 0);
}

std::pair<Types, Types> Pokemon::getType() const
{
	return _stats.getType();
}

std::pair<std::size_t, std::string> Pokemon::getEvolution() const
{
	return std::make_pair(_stats.getEvolveLvl(), _stats.getEvolve());
}

std::string Pokemon::getName() const
{
	return _name;
}

std::string Pokemon::getNickname() const
{
	return _nickname;
}

std::map<std::size_t, std::string> Pokemon::getMovepool() const
{
	return _atk.getMovepool();
}

OtterEngine::ISprite *Pokemon::getSprite() const
{
	return _sprite;
}

void Pokemon::setAngleShot(int angle)
{
	_angleShot = angle;
}

int Pokemon::getAngleShot() const
{
	return _angleShot;
}

void Pokemon::displayStats() const
{
	std::cout << "\n--- n°" << this->getId() << " " << this->getName() << " ---" << std::endl;

	std::cout << "Lvl: " << this->getLvl() << std::endl << std::endl;
	std::cout << "HP: " << this->getCurrentHp() << "/" << this->getMaxHp() << std::endl;
	std::cout << "ATK: " << this->getAtk() << std::endl;
	std::cout << "DEF: " << this->getDef() << std::endl;
	std::cout << "ATKSPE: " << this->getAtkSpe() << std::endl;
	std::cout << "DEFSPE: " << this->getDefSpe() << std::endl;
	std::cout << "SPEED: " << this->getSpeed() << std::endl << std::endl;

	std::cout << "types: " << TypeTable::getInstance()->getType(this->getType().first) << " | " << TypeTable::getInstance()->getType(this->getType().second) << std::endl << std::endl;

	std::cout << "iv[HP]: " << this->getIv("hp") << std::endl;
	std::cout << "iv[ATK]: " << this->getIv("atk") << std::endl;
	std::cout << "iv[DEF]: " << this->getIv("def") << std::endl;
	std::cout << "iv[ATKSPE]: " << this->getIv("atkSpe") << std::endl;
	std::cout << "iv[DEFSPE]: " << this->getIv("defSpe") << std::endl;
	std::cout << "iv[SPEED]: " << this->getIv("speed") << std::endl << std::endl;

	std::cout << "Capture rate: " << this->getCaptureRate() << std::endl;
	std::cout << "Exp given on death: " << this->getExpOnDeath() << std::endl;
	std::cout << "EV given on death: +" << this->getEvOnDeath().second << this->getEvOnDeath().first << std::endl << std::endl;

	std::cout << std::endl << std::endl;
}

void Pokemon::setInertness(bool in)
{
	_inertness = in;
	if (in == true) {
		addEvent(_events, OtterEngine::Event<Pokemon>("inertness", &Pokemon::endInertnessReaction, &Pokemon::endInertnessVerification));
	}
	else
		removeEvent<Pokemon>(_events, "inertness");
}

bool Pokemon::getInertness()
{
	return _inertness;
}

int Pokemon::moveLeft()
{
	if (!this->canMove())
		return -1;
	_velocity.x = -500;
	_facing = LEFT;
	return 0;
}

int Pokemon::moveLeftStop()
{
	if (!this->canMove())
		return -1;
	if (_velocity.x == -500)
		_velocity.x = 0;
	return 0;
}

int Pokemon::moveUp()
{
	if (!this->canMove())
		return -1;
	_velocity.y = -500;
	_facing = UP;
	return 0;
}

int Pokemon::moveUpStop()
{
	if (!this->canMove())
		return -1;
	if (_velocity.y == -500)
		_velocity.y = 0;
	return 0;
}

int Pokemon::moveDown()
{
	if (!this->canMove())
		return -1;
	_velocity.y = 500;
	_facing = DOWN;
	return 0;
}

int Pokemon::moveDownStop()
{
	if (!this->canMove())
		return -1;
	if (_velocity.y == 500)
		_velocity.y = 0;
	return 0;
}

int Pokemon::moveRight()
{
	float mul;

	if (!this->canMove())
		return -1;
	_velocity.x = 500;
	_facing = RIGHT;
	return 0;
}

int Pokemon::moveRightStop()
{
	if (!this->canMove())
		return -1;
	if (_velocity.x == 500)
		_velocity.x = 0;
	return 0;
}

void Pokemon::startAttack()
{
	_attacking = true;
}

void Pokemon::stopAttack()
{
	_attacking = false;
}

bool Pokemon::isAttacking() const
{
	return _attacking;
}

int Pokemon::attack(std::size_t slot, OtterEngine::Engine *oe)
{
	if (slot > 3)
		return 84;
	if (!this->canMove())
		return -1;
	Vector2d velocity(0, 0);

	switch (_facing) {
		case UP:
			velocity.y = -1000;
			break;
		case RIGHT:
			velocity.x = 1000;
			break;
		case DOWN:
			velocity.y = 1000;
			break;
		case LEFT:
			velocity.x = -1000;
			break;
	}
	if (!_atk.attack(slot, oe, velocity, this->getPos()))
		oe->_sm.addSound("ressources/sounds/" + _name + "_attack.wav");
	return 0;
}

bool Pokemon::endInertnessVerification(OtterEngine::Engine *)
{
	if (_velocity.x == 0 && _velocity.y == 0)
		return true;
	else
	{
		if (_velocity.x > 0) {
			_velocity.x -= 2;
			if (_velocity.x < 0)
				_velocity.x = 0;
		}
		else if (_velocity.x < 0) {
			_velocity.x += 2;
			if (_velocity.x > 0)
				_velocity.x = 0;
		}
		if (_velocity.y > 0) {
			_velocity.y -= 2;
			if (_velocity.y < 0)
				_velocity.y = 0;
		}
		else if (_velocity.y < 0) {
			_velocity.y += 2;
			if (_velocity.y > 0)
				_velocity.y = 0;
		}
	}
	return false;
}

int Pokemon::endInertnessReaction(OtterEngine::Engine *)
{
	_inertness = false;
	removeEvent<Pokemon>(_events, "inertness");
	return 0;
}

bool Pokemon::isDead(OtterEngine::Engine *oe)
{
	return !isAlive();
}

int Pokemon::die(OtterEngine::Engine *oe)
{
	if (rand() % 100 >= 25) {
		ItemFactory facto;
		IItems *item = facto.createItem();

		item->setPos(this->getPos());
		oe->addObject(item);
		OtterEngine::SpritesManager::getInstance()->addSprite(3, item->getSprite());
	}
	
	removeEvent(_events, "Die");
	oe->removeObject(oe->getIndex(this));
	this->hide();

	return 0;
}

bool Pokemon::UpdateVerification(OtterEngine::Engine *oe)
{
	return true;
}

int Pokemon::UpdateReaction(OtterEngine::Engine *oe)
{
	this->update(TimeManager::getInstance()->getDeltaTime());
	return 0;
}

void Pokemon::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
