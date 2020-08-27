//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// entity
//

#pragma once

#include "Object.hpp"
#include "StatsManager.hpp"
#include "AtkManager.hpp"
#include "Status.hpp"
#include "Gauge.hpp"

#define ID "id"
#define TYPE "type"
#define EV "ev"
#define EXP "exp"
#define RATE "rate"
#define MOVEPOOL "movepool"
#define EVOLVE "evolve"

class Pokemon : virtual public OtterEngine::Object
{
public:
	Pokemon(std::string name);
	Pokemon(Pokemon *pkmn);
	~Pokemon();
public:
	//getters and setters
	void setPos(Vector2d pos);
	void setBaseStat(std::pair<std::string, std::string> stat);
	void setId(std::size_t id);
	void setIv(std::string stat, std::size_t value);
	void setLvl(std::size_t lvl);
	void setNickname(std::string nickname);
	void setInertness(bool in);

	AtkManager getAtkManager()const;
	std::size_t getBaseStat(const std::string stat) const;
	bool getInertness();
	Vector2d getPos();
	std::size_t getMaxHp() const;
	std::size_t getCurrentHp() const;
	std::size_t getAtk() const;
	std::size_t getDef() const;
	std::size_t getAtkSpe() const;
	std::size_t getDefSpe() const;
	std::size_t getSpeed() const;

	std::size_t getIv(std::string iv) const;
	std::size_t getId() const;
	std::size_t getLvl() const;
	std::size_t getCaptureRate() const;
	std::size_t getExpOnDeath() const;
	std::pair<std::string, std::size_t> getEvOnDeath() const;
	std::pair<Types, Types> getType() const;
	std::pair<std::size_t, std::string> getEvolution() const;
	std::map<std::size_t, std::string> getMovepool() const;
	std::string getName() const;
	std::string getNickname() const;
	int getFacing() const;
	void setFacing(int dir);
	bool endInertnessVerification(OtterEngine::Engine*);
	int endInertnessReaction(OtterEngine::Engine*);

	bool always(OtterEngine::Engine *oe);
	int updateSprite(OtterEngine::Engine *oe);

	OtterEngine::ISprite *getSprite() const;

	void show();
	void hide();
	void hideHpBar();

	void evolve();
	void displayStats() const;
	void updateMoves();
	void update(float deltaTime);
	bool applyStatusFor(Status::Status status, float seconds);
	bool canMove() const;
	bool haveStatus(Status::Status status) const;

	//hp
	void heal(std::size_t amount);
	void fullHeal();
	bool takeDamage(Attack atk);
	bool isAlive() const;

	//on kill
	void lvlUp();
	void gainExp(std::size_t amount);
	void gainEv(std::pair<std::string, std::size_t> ev);
	
	//event
	int moveLeft();
	int moveLeftStop();

	int moveRight();
	int moveRightStop();

	int moveDown();
	int moveDownStop();

	int moveUp();
	int moveUpStop();

	//int autoAttack(OtterEngine::Engine *oe);
	int attack(std::size_t slot, OtterEngine::Engine *oe);

	void updateEvents(OtterEngine::Engine *oe);

	void setAngleShot(int angle);
	int getAngleShot() const;

	void startAttack();
	void stopAttack();
	bool isAttacking() const;
private:
	bool UpdateVerification(OtterEngine::Engine *oe);
	int UpdateReaction(OtterEngine::Engine *oe);
	
	bool isDead(OtterEngine::Engine *oe);
	int die(OtterEngine::Engine *oe);
private:
	std::string _name;
	std::string _nickname;
	std::string _evOnDeath;
	std::size_t _id;
	std::size_t _captureRate;
	bool _inertness;
	bool _attacking;

	StatsManager _stats;
	AtkManager _atk;

	std::vector<OtterEngine::Event<Pokemon>> _events;
	int _facing;
	int _angleShot;
	OtterEngine::Gauge *_hpGauge;
	OtterEngine::Gauge *_expGauge;
};
