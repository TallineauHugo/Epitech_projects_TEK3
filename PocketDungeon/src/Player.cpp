//
// EPITECH PROJECT, 2018
// pocket dungeon
// File description:
// player
//

#include <iostream>
#include "Player.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"
#include "SpritesManager.hpp"
#include "Event.hpp"
#include "MenuManager.hpp"

#define BAR_LAYER 5
#define ICON_LAYER 6
#define SELECTOR_LAYER 7
#define COIN_OFFSET 50

#define BAR_POS_X 50
#define BAR_POS_Y 25
#define ICON_SIZE 50
#define BORDER_SIZE 5
#define CURSOR_SIZE (ICON_SIZE + (BORDER_SIZE * 2))
#define BAR_SIZE_X (6 * CURSOR_SIZE)
#define BAR_SIZE_Y 60


Player::Player() : Object(), _pkmn(nullptr), _curPkmnSlot(0), _lastSwitch(0.0), _pausePlayer(false), _level(0), _nbCoin(0)
{
	_name += "Player::";

	OtterEngine::SpritesManager *sm = OtterEngine::SpritesManager::getInstance();

	_teamBar = new OtterEngine::FixedSprite();
	_teamBar->loadSpriteFromFile("ressources/icons/teamBar.png");
	_teamBar->setPosition(Vector2d(BAR_POS_X + (BAR_SIZE_X / 2), BAR_POS_Y + (BAR_SIZE_Y / 2)));
	_teamBar->setSize(Vector2d(BAR_SIZE_X, BAR_SIZE_Y));
	sm->addSprite(BAR_LAYER, _teamBar);

	_cursor = new OtterEngine::FixedSprite();
	_cursor->loadSpriteFromFile("ressources/icons/cursor.png");
	_cursor->setPosition(Vector2d(BAR_POS_X + CURSOR_SIZE / 2, BAR_POS_Y + CURSOR_SIZE / 2));
	_cursor->setSize(Vector2d(CURSOR_SIZE, CURSOR_SIZE));
	sm->addSprite(SELECTOR_LAYER, _cursor);	

	for (int i = 0; i < 6; i++) {
		_slots[i] = new OtterEngine::FixedSprite();
		_slots[i]->loadSpriteFromFile("ressources/icons/empty_icon.png");
		_slots[i]->setPosition(Vector2d(BAR_POS_X + (ICON_SIZE / 2) + BORDER_SIZE + (CURSOR_SIZE * i), BAR_POS_Y + BORDER_SIZE + ICON_SIZE / 2));
		_slots[i]->setSize(Vector2d(50, 50));
		sm->addSprite(ICON_LAYER, _slots[i]);
	}

	_coin = new OtterEngine::FixedSprite();
	_coin->loadSpriteFromFile("ressources/texture/coin_hud.png");
	_coin->setPosition(Vector2d(BAR_POS_X + BAR_SIZE_X + COIN_OFFSET + (215 / 2), BAR_POS_Y + CURSOR_SIZE / 2));
	_coin->setSize(Vector2d(215, CURSOR_SIZE));
	sm->addSprite(SELECTOR_LAYER, _coin);

	sf::Font font;
	font.loadFromFile("ressources/font/arial.ttf");

	_nbCoinSprite = new OtterEngine::TextSprite();
	_nbCoinSprite->setFont(font);
	_nbCoinSprite->setColor(sf::Color::Black);
	_nbCoinSprite->setString(": " + std::to_string(_nbCoin));
	_nbCoinSprite->setPosition(Vector2d(BAR_POS_X + BAR_SIZE_X + COIN_OFFSET + (215 / 2) + (-50), BAR_POS_Y + CURSOR_SIZE / 2 + (-15)));
	sm->addSprite(SELECTOR_LAYER, _nbCoinSprite);

	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::RightReaction, &Player::RightVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::UpReaction, &Player::UpVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::DownReaction, &Player::DownVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("LeftView", &Player::LeftViewReaction, &Player::LeftViewVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("RightView", &Player::RightViewReaction, &Player::RightViewVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("UpView", &Player::UpViewReaction, &Player::UpViewVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("DownView", &Player::DownViewReaction, &Player::DownViewVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Collide", &Player::CollideReaction, &Player::CollideVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Pause", &Player::PauseReaction, &Player::PauseVerification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Atk1", &Player::Atk1Reaction, &Player::Atk1Verification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Atk2", &Player::Atk2Reaction, &Player::Atk2Verification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Atk3", &Player::Atk3Reaction, &Player::Atk3Verification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("Atk4", &Player::Atk4Reaction, &Player::Atk4Verification));
	addEvent<Player>(_events, OtterEngine::Event<Player>("switch", &Player::SwitchReaction, &Player::SwitchVerification));
}

Player::~Player()
{

}

bool Player::addPkmnToTeam(Pokemon *pkmn)
{
	OtterEngine::SpritesManager *sm = OtterEngine::SpritesManager::getInstance();

	if (_pkmns.size() >= 6)
		return false;
	int slot = _pkmns.size();
	_pkmns[slot] = pkmn;
	if (!_pkmn) {
		_pkmn = pkmn;
		_pkmn->setIsPlayer(true);
		_curPkmnSlot = 0;
	}
	else
		pkmn->hide();
	sm->removeSprite(_slots[slot]);
	delete _slots[slot];
	_slots[slot] = new OtterEngine::FixedSprite();
	_slots[slot]->loadSpriteFromFile("ressources/icons/" + pkmn->getName() + "_icon.png");
	_slots[slot]->setPosition(Vector2d(BAR_POS_X + CURSOR_SIZE / 2 + (CURSOR_SIZE * slot), BAR_POS_Y + CURSOR_SIZE / 2));
	_slots[slot]->setSize(Vector2d(50, 50));
	sm->addSprite(ICON_LAYER, _slots[slot]);
}

Pokemon *Player::addPkmnToTeamSlot(Pokemon *pkmn, std::size_t slot)
{
	OtterEngine::SpritesManager *sm = OtterEngine::SpritesManager::getInstance();
	Pokemon *ret = nullptr;

	if (slot >= 6)
		return ret;
	if (_pkmns.find(slot) != _pkmns.end())
		ret = _pkmns[slot];
	_pkmns[slot] = pkmn;
	if (!_pkmn || slot == _curPkmnSlot)
		_pkmn = pkmn;
	else
		pkmn->hide();
	_slots[slot]->loadSpriteFromFile("ressources/icons/" + pkmn->getName() + "_icon.png");
	_slots[slot]->setPosition(Vector2d(50 + 5 + (60 * slot) + 25, 50 + 5 + 25));
	_slots[slot]->setSize(Vector2d(50, 50));
	sm->addSprite(ICON_LAYER, _slots[slot]);

	return ret;
}

bool Player::switchNext()
{
	int tmp;

	for (std::size_t i = _curPkmnSlot + 1; i < 6; i++) {
		if (_pkmns.find(i) != _pkmns.end()) {
			tmp = _pkmn->getFacing();
			_pkmn = _pkmns[i];
			_pkmn->setFacing(tmp);
			_pkmn->stopAttack();
			_pkmn->setInertness(true);
			_curPkmnSlot = i;
			_cursor->setPosition(Vector2d(BAR_POS_X + 30 + (CURSOR_SIZE * i), BAR_POS_Y + 30));
			return true;
		}
	}
	for (std::size_t i = 0; i < _curPkmnSlot; i++) {
		if (_pkmns.find(i) != _pkmns.end()) {
			tmp = _pkmn->getFacing();
			_pkmn = _pkmns[i];
			_pkmn->stopAttack();
			_pkmn->setInertness(true);
			_pkmn->setFacing(tmp);
			_curPkmnSlot = i;
			_cursor->setPosition(Vector2d(BAR_POS_X + 30 + (CURSOR_SIZE * i), BAR_POS_Y + 30));
			return true;
		}
	}
	return false;
}

bool Player::switchWithSlot(std::size_t slot)
{
	int tmp;

	if (_pkmns.find(slot) != _pkmns.end()) {
			tmp = _pkmn->getFacing();
			_pkmn = _pkmns[slot];
			_pkmn->setFacing(tmp);
			_pkmn->stopAttack();
			_pkmn->setInertness(true);
			_curPkmnSlot = slot;
			_cursor->setPosition(Vector2d(50 + 30 + (60 * slot), 50 + 30));
			return true;
	}
	return false;
}

bool Player::heal(std::size_t amount)
{
	if (!_pkmn || (_pkmn->getMaxHp() == _pkmn->getCurrentHp()))
		return false;
	_pkmn->heal(amount);
	return true;
}

bool Player::gainExp(std::size_t amount)
{
	if (!_pkmn || (_pkmn->getLvl() >= 100))
		return false;
	_pkmn->gainExp(amount);
	return true;
}

/*void Player::setCurrentPokemon(Pokemon *pkmn)
{
	if (_pkmn)
		_pkmn->setIsPlayer(false);
	_pkmn = pkmn;
	_pkmn->setIsPlayer(true);
}*/

int Player::getLevel()
{
	return _level;
}

void Player::setLevel(int level)
{
	_level = level;
}

void Player::updateLevel()
{
	std::size_t maxlevel = 0;

	for (std::map<int, Pokemon *>::const_iterator it = _pkmns.begin(); it != _pkmns.end(); ++it)
	{
		if (it->second->getLvl() > maxlevel)
			maxlevel = it->second->getLvl();
	}
	if (maxlevel / 7 > _level)
		_level = maxlevel / 7;
}

Pokemon *Player::GetCurrentPokemon(void)
{
	return _pkmn;
}

bool Player::LeftVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Q);
}

bool Player::NoLeftVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (!InputManager::getInstance()->isKeyPressed(sf::Keyboard::Q))
		return true;
	else {
		Vector2d tmp = _pkmn->getVelocity();
		if (tmp.x == 0 && tmp.y == 0 && _pkmn->getFacing() == LEFT && !_pkmn->isAttacking())
			_pkmn->setVelocity({-500, tmp.y});
		return false;
	}
}

int Player::LeftReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness() || _pkmn->isAttacking())
		return 0;
	_pkmn->moveLeft();
	removeEvent(_events, "Left");
	addEvent<Player>(_events, OtterEngine::Event<Player>("NoLeft", &Player::NoLeftReaction, &Player::NoLeftVerification));
	return 0;
}

int Player::NoLeftReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness())
		return 0;
	_pkmn->moveLeftStop();
	removeEvent(_events, "NoLeft");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Left", &Player::LeftReaction, &Player::LeftVerification));
	return 0;
}

bool Player::UpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

bool Player::NoUpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (!InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z))
		return true;
	else {
		Vector2d tmp = _pkmn->getVelocity();
		if (tmp.x == 0 && tmp.y == 0 &&_pkmn->getFacing() == UP && !_pkmn->isAttacking())
			_pkmn->setVelocity({tmp.x, -500});
		return false;
	}
}

int Player::UpReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness() == true || _pkmn->isAttacking()) {
		std::cout << "Can't go up: inertness = true\n";
		return 0;
	}
	else {
		std::cout << "inertness = false\n";
	}
	_pkmn->moveUp();
	removeEvent(_events, "Up");
	addEvent<Player>(_events, OtterEngine::Event<Player>("NoUp", &Player::NoUpReaction, &Player::NoUpVerification));
	return 0;
}

int Player::NoUpReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness())
		return 0;
	_pkmn->moveUpStop();
	removeEvent(_events, "NoUp");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Up", &Player::UpReaction, &Player::UpVerification));
	return 0;
}

bool Player::DownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

bool Player::NoDownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (!InputManager::getInstance()->isKeyPressed(sf::Keyboard::S))
		return true;
	else {
		Vector2d tmp = _pkmn->getVelocity();
		if (tmp.x == 0 && tmp.y == 0 && _pkmn->getFacing() == DOWN && !_pkmn->isAttacking())
			_pkmn->setVelocity({tmp.x, 500});
		return false;
	}
}

int Player::DownReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness() || _pkmn->isAttacking())
		return 0;
	_pkmn->moveDown();
	removeEvent(_events, "Down");
	addEvent<Player>(_events, OtterEngine::Event<Player>("NoDown", &Player::NoDownReaction, &Player::NoDownVerification));
	return 0;
}

int Player::NoDownReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness())
		return 0;
	_pkmn->moveDownStop();
	removeEvent(_events, "NoDown");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Down", &Player::DownReaction, &Player::DownVerification));
	return 0;
}

bool Player::RightVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::D);
}

bool Player::NoRightVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (!InputManager::getInstance()->isKeyPressed(sf::Keyboard::D))
		return true;
	else {
		Vector2d tmp = _pkmn->getVelocity();
		if (tmp.x == 0 && tmp.y == 0 && _pkmn->getFacing() == RIGHT && !_pkmn->isAttacking())
			_pkmn->setVelocity({500, tmp.y});
		return false;
	}
}

int Player::RightReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness() || _pkmn->isAttacking())
		return 0;
	_pkmn->moveRight();
	removeEvent(_events, "Right");
	addEvent<Player>(_events, OtterEngine::Event<Player>("NoRight", &Player::NoRightReaction, &Player::NoRightVerification));
	return 0;
}

int Player::NoRightReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	if (_pkmn->getInertness())
		return 0;
	_pkmn->moveRightStop();
	removeEvent(_events, "NoRight");
	addEvent<Player>(_events, OtterEngine::Event<Player>("Right", &Player::RightReaction, &Player::RightVerification));
	return 0;
}

bool Player::LeftViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Left);
}

bool Player::UpViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Up);
}

bool Player::RightViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Right);
}

bool Player::DownViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Down);
}

int Player::LeftViewReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 0)
		_pkmn->setAngleShot(45);
	else if (_pkmn->getAngleShot() == 180)
		_pkmn->setAngleShot(135);
	else
		_pkmn->setAngleShot(90);
}

int Player::RightViewReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 0)
		_pkmn->setAngleShot(315);
	else if (_pkmn->getAngleShot() == 180)
		_pkmn->setAngleShot(225);
	else
		_pkmn->setAngleShot(270);
}

int Player::DownViewReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 90)
		_pkmn->setAngleShot(45);
	else if (_pkmn->getAngleShot() == 270)
		_pkmn->setAngleShot(315);
	else
		_pkmn->setAngleShot(0);
}

int Player::UpViewReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 90)
		_pkmn->setAngleShot(135);
	else if (_pkmn->getAngleShot() == 270)
		_pkmn->setAngleShot(225);
	else
		_pkmn->setAngleShot(180);
}


bool Player::Atk1Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num1);
}

int Player::Atk1Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->attack(0, oe);
	return 0;
}

bool Player::Atk2Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num2);
}

int Player::Atk2Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->attack(1, oe);
	return 0;
}

bool Player::Atk3Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num3);
}

int Player::Atk3Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->attack(2, oe);
	return 0;
}

bool Player::Atk4Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num4);
}

int Player::Atk4Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->attack(3, oe);
	return 0;
}

bool Player::CollideVerification(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(_pkmn);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();
	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end(); it++){
		if ((it->first == i && (objs[it->second]->getName().find("Wall") != std::string::npos || dynamic_cast<Pokemon *>(objs[it->second]) != nullptr))
		     || (it->second == i && (objs[it->first]->getName().find("Wall") != std::string::npos || dynamic_cast<Pokemon *>(objs[it->first]) != nullptr)))
			return true;
	}
	return false;
}

int Player::CollideReaction(OtterEngine::Engine *oe)
{
	this->_pkmn->getHitbox().applyLPos();
	this->_pkmn->setVelocity(Vector2d(0,0));
}

bool Player::PauseVerification(OtterEngine::Engine *oe)
{
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::P);
	// if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::P))
	// {
	// 	_pkmn->setVelocity(Vector2d(0, 0));
	// 	return true;
	// }
	// return false;
}

int Player::PauseReaction(OtterEngine::Engine *oe)
{
	std::cout << "Pause from player" << std::endl;
	MenuManager::getInstance()->getInGameMenuInstance(oe);
}

/*bool Player::AutoVerification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Space);
}

int Player::AutoReaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->autoAttack(oe);
	return 0;
}*/

bool Player::SwitchVerification(OtterEngine::Engine *oe)
{
	if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::E))
		return true;
	return false;
}

int Player::SwitchReaction(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();
	Vector2d pos;

	if (_pkmn && _pkmn->isAttacking())
		return 0;
	if (_lastSwitch > elapsedTime || elapsedTime - _lastSwitch > 1.0) {
		_lastSwitch = elapsedTime;
		pos = _pkmn->getPos();
		_pkmn->setIsPlayer(false);
		_pkmn->hide();
		//OtterEngine::SpritesManager::getInstance()->removeSprite(_pkmn->getSprite());
		oe->removeObject(oe->getIndex(_pkmn));
		this->switchNext();
		_pkmn->setIsPlayer(true);
		_pkmn->setPos(pos);
		_pkmn->setVelocity(Vector2d(0, 0));
		oe->addObject(_pkmn);
		_pkmn->show();
		//OtterEngine::SpritesManager::getInstance()->addSprite(3, _pkmn->getSprite());
		return 0;
	}
	return 1;
}

void Player::updateEvents(OtterEngine::Engine *oe)
{
	_hitbox = _pkmn->getHitbox();
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}


void Player::respawn(OtterEngine::Engine *oe)
{
	std::cout << "respawn !\n";
	GetCurrentPokemon()->fullHeal();
	GetCurrentPokemon()->show();
	oe->addObject(GetCurrentPokemon());
}

std::size_t Player::getNbCoin() const
{
	return _nbCoin;
}

void Player::gainCoin(std::size_t nb)
{
	_nbCoin += nb;
	_nbCoinSprite->setString(": " + std::to_string(_nbCoin));
}