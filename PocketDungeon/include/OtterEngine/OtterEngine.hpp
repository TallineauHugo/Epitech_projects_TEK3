#pragma once

#include "define.hpp"
#include "MusicManager.hpp"
#include "SoundManager.hpp"
#include "SpritesManager.hpp"
#include <list>

class IA;

class OtterEngine::Engine
{
public:
	Engine();
	~Engine();

	std::vector<Object *>& getObjs();
	std::vector<IA *>& getListIA();
	OtterEngine::Object *getObjectById(std::size_t id) const;
	std::map<int, int>& getCols();
	std::list<std::size_t> getRemovedList();

	void setGraphicalMode(bool);
	void addObject(Object *);
	void addIA(IA *);
	int getIndex(Object *);
	void removeObject(int);
	void removeObjectById(std::size_t);
	int update();
	void updateIA(bool);
	void pause();
	void clearEngine();
	void removeIAs();
	void restart();
	void normalize();
	bool getPause();

	MusicManager _mm;
	SoundManager _sm;

private:
	void removeObjects();
	void calculateColisions();
	void checkEvents();
	void applyVelo();

	std::vector<Object *> _objs;
	std::map<int, int> _cols;
	std::list<int> _removeList;
	std::list<std::size_t> _removedList;
	bool _graph;
	bool _pause;
	std::vector<IA *> _ListIA;
	int _quit;
};
