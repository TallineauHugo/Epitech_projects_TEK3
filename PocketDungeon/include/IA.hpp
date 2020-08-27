//
// EPITECH PROJECT, 2018
// pocket dungeon
// File description:
// player
//

#pragma once

#include <vector>

#include "Pokemon.hpp"
#include "Player.hpp"
#include "OtterEngine.hpp"

class IA : public virtual OtterEngine::Object
{
public:
	IA(OtterEngine::Engine *oe, Player *player);
	~IA();
public:
	void setCurrentPokemon(Pokemon *pkmn);
	Pokemon *GetCurrentPokemon(void);
	Player *getPlayer(void);

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

	bool Atk1Verification(OtterEngine::Engine *oe);
	int Atk1Reaction(OtterEngine::Engine *oe);
	bool Atk2Verification(OtterEngine::Engine *oe);
	int Atk2Reaction(OtterEngine::Engine *oe);
	bool Atk3Verification(OtterEngine::Engine *oe);
	int Atk3Reaction(OtterEngine::Engine *oe);
	bool Atk4Verification(OtterEngine::Engine *oe);
	int Atk4Reaction(OtterEngine::Engine *oe);

	void update(OtterEngine::Engine *oe);
private:
	Pokemon *_pkmn;
	std::vector<OtterEngine::Event<IA>> _events;
        OtterEngine::Engine *_oe;
	Player*_Player;
};
