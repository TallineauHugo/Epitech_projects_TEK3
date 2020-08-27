#include "WindowManager.hpp"
#include "MonsterGenerator.hpp"
#include "ZigZagEnnemy.hpp"
#include "TimeManager.hpp"
#include <string.h>
#include <iostream>
#include <dlfcn.h>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>

MonsterGenerator::MonsterGenerator() : _threat(1)
{
	_name += "MonsterGenerator::";
	addEvent<MonsterGenerator>(_events, OtterEngine::Event<MonsterGenerator>("timeForNextWave", &MonsterGenerator::timeForNextWaveReaction, &MonsterGenerator::timeForNextWaveVerification));
}

MonsterGenerator::~MonsterGenerator()
{

}


bool MonsterGenerator::timeForNextWaveVerification(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();
	
	return (_lastWave > elapsedTime || elapsedTime - _lastWave > 8.0);
}

void MonsterGenerator::checkNewMonsters(OtterEngine::Engine *oe)
{
	DIR* dirp = opendir("./Game/Ennemies");
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		if (strlen(dp->d_name) > 2 && std::find(_files.begin(), _files.end(), std::string(dp->d_name)) == _files.end())
		_files.push_back(dp->d_name);
	}
	closedir(dirp);
	for (unsigned int i = 0; i < _files.size(); i++) {
		char            *error;
		void		*lol;
		EnnemySpaceShip *(*entry)();

		lol = dlopen(std::string("./Game/Ennemies/" + _files[i]).c_str(), RTLD_LAZY);
		error = dlerror();
		if (!lol)
			exit(84);
		entry = (EnnemySpaceShip *(*)())dlsym(lol, "entryPoint");
		error = dlerror();
		if (error)
			exit(84);
		_monsters.insert(std::pair<std::string, EnnemySpaceShip *>(_files[i], (*entry)()));
	}
}

int MonsterGenerator::timeForNextWaveReaction(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();

	_lastWave = elapsedTime;
	checkNewMonsters(oe);
	static int wave = 0;
	int level = _threat;
	int i;
	
	wave = (wave + 1 % 3) ? wave = 0 : wave + 1;
	_threat+= (wave) ? 0 : 1;
	while (level > 0) {
		std::map<std::string , EnnemySpaceShip*>::iterator i = _monsters.begin();
		for (int i2 = rand() % _monsters.size(); i2 > 0; i2--)
			i++;
		if (i->second->getThreat() <= level) {
			level -= i->second->getThreat();
			EnnemySpaceShip *newMob = i->second->clone();
			newMob->setPos(Vector2d(rand() % 500 + WindowManager::getInstance()->getSize().x, WindowManager::getInstance()->getSize().y / 2 + rand() % WindowManager::getInstance()->getSize().y));
			oe->addObject(newMob);
		}
			
	}
}

void MonsterGenerator::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

