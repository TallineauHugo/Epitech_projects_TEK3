//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon factory
//

#include "DungeonFactory.hpp"
#include "OtterEngine.hpp"

DungeonFactory::DungeonFactory()
{}

DungeonFactory::~DungeonFactory()
{}

Dungeon *DungeonFactory::createDungeon(int level, OtterEngine::Engine *oe)
{
	Dungeon *dungeon = new Dungeon(level, oe);
	// dungeon->loadDungeon();
	return dungeon;
}
