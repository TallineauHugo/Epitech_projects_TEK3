#pragma once

#include "SpaceShip.hpp"
#include "Gauge.hpp"

class Player : virtual public SpaceShip
{
public:
	Player(Vector2d pos, std::size_t id);
	~Player();
	
	void StartMoveUp();
	void StartMoveRight();
	void StartMoveDown();
	void StartMoveLeft();
	void StartShoot();
	void StartBomb();
	void StopMoveUp();
	void StopMoveRight();
	void StopMoveDown();
	void StopMoveLeft();
	void StopShoot();
	void StopBomb();

	bool ShootVerification(OtterEngine::Engine *);
	bool LeftVerification(OtterEngine::Engine *);
	bool NoLeftVerification(OtterEngine::Engine *);
	bool UpVerification(OtterEngine::Engine *);
	bool NoUpVerification(OtterEngine::Engine *);
	bool RightVerification(OtterEngine::Engine *);
	bool NoRightVerification(OtterEngine::Engine *);
	bool DownVerification(OtterEngine::Engine *);
	bool NoDownVerification(OtterEngine::Engine *);

	int ShootReaction(OtterEngine::Engine *);
	int LeftReaction(OtterEngine::Engine *);
	int NoLeftReaction(OtterEngine::Engine *);
	int UpReaction(OtterEngine::Engine *);
	int NoUpReaction(OtterEngine::Engine *);
	int RightReaction(OtterEngine::Engine *);
	int NoRightReaction(OtterEngine::Engine *);
	int DownReaction(OtterEngine::Engine *);
	int NoDownReaction(OtterEngine::Engine *);


	bool CollideEnnemyVerification(OtterEngine::Engine *);
	bool CollideEnergyVerification(OtterEngine::Engine *);
	int CollideEnnemyReaction(OtterEngine::Engine *);
	int CollideEnergyReaction(OtterEngine::Engine *);

	bool hasEnergyVerification(OtterEngine::Engine *oe);
	int hasEnergyReaction(OtterEngine::Engine *oe);
	bool BombShootVerification(OtterEngine::Engine *oe);
	int BombShootReaction(OtterEngine::Engine *oe);
	
	void updateEvents(OtterEngine::Engine*);
private:
	std::vector<OtterEngine::Event<Player>> _events;
	int _energy;
	bool _dir[4];
	bool _shoot;
	bool _bomb;

	OtterEngine::Gauge *_gauge;
};
