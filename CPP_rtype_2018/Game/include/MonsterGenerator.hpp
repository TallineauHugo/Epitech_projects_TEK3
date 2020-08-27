#include "Object.hpp"
#include "EnnemySpaceShip.hpp"

class MonsterGenerator : public virtual OtterEngine::Object
{
public:
	MonsterGenerator();
	~MonsterGenerator();

	bool timeForNextWaveVerification(OtterEngine::Engine *oe);
	int timeForNextWaveReaction(OtterEngine::Engine *oe);
	
	void updateEvents(OtterEngine::Engine *oe);
	
private:
	void checkNewMonsters(OtterEngine::Engine *oe);
	std::map<std::string, EnnemySpaceShip *> _monsters;
	std::vector<std::string> _files;
	std::vector<OtterEngine::Event<MonsterGenerator>> _events;
	int _threat;
	float _lastWave;
};
