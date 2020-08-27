//
// EPITECH PROJECT, 2018
// pocket dungeon
// File description:
// IA
//

#include <iostream>
#include "IA.hpp"
#include "InputManager.hpp"
#include "Event.hpp"

IA::IA(OtterEngine::Engine *oe, Player *player) : Object(), _pkmn(nullptr), _oe(oe), _Player(player)
{
	_name += "IA::";
	addEvent<IA>(_events, OtterEngine::Event<IA>("Left", &IA::LeftReaction, &IA::LeftVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Right", &IA::RightReaction, &IA::RightVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Up", &IA::UpReaction, &IA::UpVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Down", &IA::DownReaction, &IA::DownVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("LeftView", &IA::LeftViewReaction, &IA::LeftViewVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("RightView", &IA::RightViewReaction, &IA::RightViewVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("UpView", &IA::UpViewReaction, &IA::UpViewVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("DownView", &IA::DownViewReaction, &IA::DownViewVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Collide", &IA::CollideReaction, &IA::CollideVerification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Atk1", &IA::Atk1Reaction, &IA::Atk1Verification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Atk2", &IA::Atk2Reaction, &IA::Atk2Verification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Atk3", &IA::Atk3Reaction, &IA::Atk3Verification));
	addEvent<IA>(_events, OtterEngine::Event<IA>("Atk4", &IA::Atk4Reaction, &IA::Atk4Verification));
        _oe->addIA(this);
}

IA::~IA()
{

}

Player *IA::getPlayer(void) {
	return _Player;
}

void IA::setCurrentPokemon(Pokemon *pkmn)
{
	_pkmn = pkmn;
}

Pokemon *IA::GetCurrentPokemon(void)
{
	return _pkmn;
}

bool IA::LeftVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Q);
}

bool IA::NoLeftVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Q);
}

int IA::LeftReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveLeft();
	removeEvent(_events, "Left");
	addEvent<IA>(_events, OtterEngine::Event<IA>("NoLeft", &IA::NoLeftReaction, &IA::NoLeftVerification));
	return 0;
}

int IA::NoLeftReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveLeftStop();
	removeEvent(_events, "NoLeft");
	addEvent<IA>(_events, OtterEngine::Event<IA>("Left", &IA::LeftReaction, &IA::LeftVerification));
	return 0;
}

bool IA::UpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

bool IA::NoUpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::Z);
}

int IA::UpReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveUp();
	removeEvent(_events, "Up");
	addEvent<IA>(_events, OtterEngine::Event<IA>("NoUp", &IA::NoUpReaction, &IA::NoUpVerification));
	return 0;
}

int IA::NoUpReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveUpStop();
	removeEvent(_events, "NoUp");
	addEvent<IA>(_events, OtterEngine::Event<IA>("Up", &IA::UpReaction, &IA::UpVerification));
	return 0;
}

bool IA::DownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

bool IA::NoDownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::S);
}

int IA::DownReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveDown();
	removeEvent(_events, "Down");
	addEvent<IA>(_events, OtterEngine::Event<IA>("NoDown", &IA::NoDownReaction, &IA::NoDownVerification));
	return 0;
}

int IA::NoDownReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveDownStop();
	removeEvent(_events, "NoDown");
	addEvent<IA>(_events, OtterEngine::Event<IA>("Down", &IA::DownReaction, &IA::DownVerification));
	return 0;
}

bool IA::RightVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::D);
}

bool IA::NoRightVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return !InputManager::getInstance()->isKeyPressed(sf::Keyboard::D);
}

int IA::RightReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveRight();
	removeEvent(_events, "Right");
	addEvent<IA>(_events, OtterEngine::Event<IA>("NoRight", &IA::NoRightReaction, &IA::NoRightVerification));
	return 0;
}

int IA::NoRightReaction(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return 0;
	if (!_pkmn)
		return 84;
	_pkmn->moveRightStop();
	removeEvent(_events, "NoRight");
	addEvent<IA>(_events, OtterEngine::Event<IA>("Right", &IA::RightReaction, &IA::RightVerification));
	return 0;
}


bool IA::LeftViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Left);
}

bool IA::UpViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Up);
}

bool IA::RightViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Right);
}

bool IA::DownViewVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Down);
}

int IA::LeftViewReaction(OtterEngine::Engine *oe)
{
	/*if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getHitbox().getAngle() == 0)
		_pkmn->getHitbox().setAngle(45);
	else if (_pkmn->getHitbox().getAngle() == 180)
		_pkmn->getHitbox().setAngle(135);
	else
		_pkmn->getHitbox().setAngle(90);*/

	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 0)
		_pkmn->setAngleShot(45);
	else if (_pkmn->getAngleShot() == 180)
		_pkmn->setAngleShot(135);
	else
		_pkmn->setAngleShot(90);
}

int IA::RightViewReaction(OtterEngine::Engine *oe)
{
	/*if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getHitbox().getAngle() == 0)
		_pkmn->getHitbox().setAngle(315);
	else if (_pkmn->getHitbox().getAngle() == 180)
		_pkmn->getHitbox().setAngle(225);
	else
		_pkmn->getHitbox().setAngle(270);*/
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 0)
		_pkmn->setAngleShot(315);
	else if (_pkmn->getAngleShot() == 180)
		_pkmn->setAngleShot(225);
	else
		_pkmn->setAngleShot(270);
}

int IA::DownViewReaction(OtterEngine::Engine *oe)
{
	/*if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getHitbox().getAngle() == 90)
		_pkmn->getHitbox().setAngle(45);
	else if (_pkmn->getHitbox().getAngle() == 270)
		_pkmn->getHitbox().setAngle(315);
	else
		_pkmn->getHitbox().setAngle(0);*/
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 90)
		_pkmn->setAngleShot(45);
	else if (_pkmn->getAngleShot() == 270)
		_pkmn->setAngleShot(315);
	else
		_pkmn->setAngleShot(0);
}

int IA::UpViewReaction(OtterEngine::Engine *oe)
{
	/*if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getHitbox().getAngle() == 90)
		_pkmn->getHitbox().setAngle(135);
	else if (_pkmn->getHitbox().getAngle() == 270)
		_pkmn->getHitbox().setAngle(225);
	else
		_pkmn->getHitbox().setAngle(180);*/
	if (_pkmn->getInertness())
		return 0;
	if (_pkmn->getAngleShot() == 90)
		_pkmn->setAngleShot(135);
	else if (_pkmn->getAngleShot() == 270)
		_pkmn->setAngleShot(225);
	else
		_pkmn->setAngleShot(180);
}


bool IA::Atk1Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num1);
}

int IA::Atk1Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->attack(0, oe);
	std::cout << "IA angle shot: " << _pkmn->getAngleShot() << std::endl;
	return 0;
}

bool IA::Atk2Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num2);
}

int IA::Atk2Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	std::cout << "IA angle shot: " << _pkmn->getAngleShot() << std::endl;
	_pkmn->attack(1, oe);
	return 0;
}

bool IA::Atk3Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num3);
}

int IA::Atk3Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	_pkmn->attack(2, oe);
	std::cout << "IA angle shot: " << _pkmn->getAngleShot() << std::endl;
	return 0;
}

bool IA::Atk4Verification(OtterEngine::Engine *oe)
{
	if (_pkmn->getInertness())
		return false;
	(void)oe;
	return InputManager::getInstance()->isKeyPressed(sf::Keyboard::Num4);
}

int IA::Atk4Reaction(OtterEngine::Engine *oe)
{
	if (!_pkmn)
		return 84;
	std::cout << "IA angle shot: " << _pkmn->getAngleShot() << std::endl;
	_pkmn->attack(3, oe);
	return 0;
}

bool IA::CollideVerification(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();
	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if ((it->first == i && objs[it->second]->getName().find("Wall") != std::string::npos)
		    || (it->second == i && objs[it->first]->getName().find("Wall") != std::string::npos))
			return true;
	}
	return false;
}

int IA::CollideReaction(OtterEngine::Engine *oe)
{
	this->_hitbox.applyLPos();
	_velocity.x = _velocity.y = 0;
}

void IA::updateEvents(OtterEngine::Engine *oe)
{
	_hitbox = _pkmn->getHitbox();
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
