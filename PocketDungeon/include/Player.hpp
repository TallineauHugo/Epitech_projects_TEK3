//
// EPITECH PROJECT, 2018
// pocket dungeon
// File description:
// player
//

#pragma once

#include <vector>

#include "Pokemon.hpp"
#include "OtterEngine.hpp"
#include "FixedSprite.hpp"
#include "TextSprite.hpp"

class Player : public virtual OtterEngine::Object
{
public:
	Player();
	~Player();
public:
	bool addPkmnToTeam(Pokemon *pkmn);
	Pokemon *addPkmnToTeamSlot(Pokemon *pkmn, std::size_t slot);
	bool switchNext();
	bool switchWithSlot(std::size_t slot);
	void respawn(OtterEngine::Engine *oe);

	bool heal(std::size_t amount);
	bool gainExp(std::size_t amount);

	int getLevel();
	void setLevel(int);

	void updateLevel();
	//void setCurrentPokemon(Pokemon *pkmn);
	Pokemon *GetCurrentPokemon(void);

	void gainCoin(std::size_t nb);
	std::size_t getNbCoin() const;

	virtual void updateEvents(OtterEngine::Engine *oe);

	bool LeftVerification(OtterEngine::Engine *oe);
	bool UpVerification(OtterEngine::Engine *oe);
	bool RightVerification(OtterEngine::Engine *oe);
	bool DownVerification(OtterEngine::Engine *oe);
	bool NoLeftVerification(OtterEngine::Engine *oe);
	bool NoUpVerification(OtterEngine::Engine *oe);
	bool NoRightVerification(OtterEngine::Engine *oe);
	bool NoDownVerification(OtterEngine::Engine *oe);

	bool LeftViewVerification(OtterEngine::Engine *oe);
	bool UpViewVerification(OtterEngine::Engine *oe);
	bool RightViewVerification(OtterEngine::Engine *oe);
	bool DownViewVerification(OtterEngine::Engine *oe);

	int LeftViewReaction(OtterEngine::Engine *oe);
	int RightViewReaction(OtterEngine::Engine *oe);
	int DownViewReaction(OtterEngine::Engine *oe);
	int UpViewReaction(OtterEngine::Engine *oe);

	int LeftReaction(OtterEngine::Engine *oe);
	int RightReaction(OtterEngine::Engine *oe);
	int DownReaction(OtterEngine::Engine *oe);
	int UpReaction(OtterEngine::Engine *oe);
	int NoLeftReaction(OtterEngine::Engine *oe);
	int NoRightReaction(OtterEngine::Engine *oe);
	int NoDownReaction(OtterEngine::Engine *oe);
	int NoUpReaction(OtterEngine::Engine *oe);

	bool CollideVerification(OtterEngine::Engine *oe);
	int CollideReaction(OtterEngine::Engine *oe);

	bool PauseVerification(OtterEngine::Engine *oe);
	int PauseReaction(OtterEngine::Engine *oe);

	bool Atk1Verification(OtterEngine::Engine *oe);
	int Atk1Reaction(OtterEngine::Engine *oe);
	bool Atk2Verification(OtterEngine::Engine *oe);
	int Atk2Reaction(OtterEngine::Engine *oe);
	bool Atk3Verification(OtterEngine::Engine *oe);
	int Atk3Reaction(OtterEngine::Engine *oe);
	bool Atk4Verification(OtterEngine::Engine *oe);
	int Atk4Reaction(OtterEngine::Engine *oe);

	bool SwitchVerification(OtterEngine::Engine *oe);
	int SwitchReaction(OtterEngine::Engine *oe);
private:

private:
	Pokemon *_pkmn;
	std::size_t _curPkmnSlot;
	float _lastSwitch;
	std::map<int, Pokemon *> _pkmns;
	int _level;
	std::vector<OtterEngine::Event<Player>> _events;
	bool _pausePlayer;
	std::size_t _nbCoin;

	OtterEngine::FixedSprite *_teamBar;
	OtterEngine::FixedSprite *_cursor;
	OtterEngine::FixedSprite *_slots[6];
	OtterEngine::FixedSprite *_coin;
	OtterEngine::TextSprite *_nbCoinSprite;
};
