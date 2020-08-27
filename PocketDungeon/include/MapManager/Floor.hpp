#pragma once

#include <map>
#include "DungeonRoom.hpp"
#include "Dungeon.hpp"
#include <SFML/System.hpp>

class Floor {
public:
        Floor(int level, OtterEngine::Engine *oe, int number, Dungeon *_dj);
        ~Floor();
        void generateMaze(void);
        void printMaze(void);
        void setCurrentRoom(int);
        int getCurrentRoom(void) const;
        DungeonRoom *getCurrentRoomObj(void);
        void enterCurrentRoom(void);
        OtterEngine::Engine *getOe(void);
        Dungeon *getDungeon(void);
private:
        OtterEngine::Engine *_oe;
        Dungeon *_dj;
        std::map<int, DungeonRoom*> _roomMapping;
        int _level;
        int _nbRoom;
        int _currentRoom;
        int _number;
};
