#pragma once

#include "define.hpp"
#include "MusicManager.hpp"
#include "SoundManager.hpp"
#include "SpritesManager.hpp"

#include <list>

class OtterEngine::Engine
{
public:
	Engine();
	~Engine();

	std::vector<Object *>& getObjs();
	OtterEngine::Object *getObjectById(std::size_t id) const;
	std::map<int, int>& getCols();
	std::list<std::size_t> getRemovedList();
	
	void setGraphicalMode(bool);
	void addObject(Object *);
	int getIndex(Object *);
	void removeObject(int);
	void removeObjectById(std::size_t);
	void update();
	MusicManager _mm;
	SoundManager _sm;
	
private:
	void calculateColisions();
	void checkEvents();
	void removeObjects();
	void applyVelo();
	
	std::vector<Object *> _objs;
	std::map<int, int> _cols;
	std::list<int> _removeList;
	std::list<std::size_t> _removedList;
	bool _graph;
};
