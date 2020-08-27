//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// attack
//

#pragma once

#include <string>
#include "Types.hpp"
#include "Object.hpp"
#include "OtterEngine.hpp"
#include "Event.hpp"
#include "Pokemon.hpp"


class Attack : public virtual OtterEngine::Object
{
public:
	Attack(Attack *atk, Vector2d velocity, Vector2d pos);
	Attack(std::string name, std::size_t dmg, std::size_t hit, float critRate, DamageType type, Types element, Pokemon *host, float range);
	~Attack();
	virtual Attack *clone(Attack *atk, Vector2d velocity, Vector2d pos);
public:
	std::string getAtkName() const;
	std::size_t getPower() const;
	std::size_t getHit() const;
	float getRange()const;
	float getCritRate() const;
	DamageType getType() const;
	Types getElement() const;
	Pokemon *getHost() const;

	void setHost(Pokemon *pkmn);
	void show();
	void hide();

	bool fadeVerification(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int fadeReaction(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);

	virtual void updateEvents(OtterEngine::Engine *oe);
protected:
	std::string _atkName;
	std::size_t _power;
	std::size_t _hit;
	float _critRate;
	DamageType _type;
	Types _element;
	Pokemon *_host;
	Vector2d _aim;
	float _range;
	Vector2d _oldVelo;

private:
	std::vector<OtterEngine::Event<Attack>> _events;
};
