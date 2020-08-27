#include <iostream>
#include <cstdlib>
#include <vector>
#include "time.h"
#include "Floor.hpp"

Floor::Floor(int level, OtterEngine::Engine *oe, int number, Dungeon *dj) : _level(level), _currentRoom(0), _oe(oe), _number(number), _dj(dj)
{
        /*
        ** DEBBUG
        */

        _nbRoom = rand() % 4 + (3 + _level);
        /*
        ** DEBBUG
        */

        for (int i = 0; i < _nbRoom; i++) {
                DungeonRoom *room = new DungeonRoom(std::to_string(i), _level, _oe, this);
                _roomMapping.insert(std::pair<int, DungeonRoom*>(i, room));
        }
        _roomMapping[0]->setIsEmpty(true);
        int random = rand() % (_nbRoom - 1) + 1;
        _roomMapping[random]->addExit();
        generateMaze();
        random = rand() % (_nbRoom - 1) + 1;
        printMaze();
        /*
        ** DEBBUG
        */
        // printMaze();
}

Floor::~Floor()
{
        std::cout << "\n\n\n" << std::endl;
        printMaze();
}

void Floor::enterCurrentRoom(void)
{
        _roomMapping[_currentRoom]->enter();
}

void Floor::generateMaze(void)
{
        int random = rand() % 4;
        int randomRoom;
        int cpt = 0;
        std::vector<int> availableRoom;

        availableRoom.push_back(0);
        for (int i = 1; i < _nbRoom; i++) {
                randomRoom = rand() % availableRoom.size();
                random = rand() % 4;
                while (!_roomMapping[i]->addRoom(_roomMapping[randomRoom], random, false)) {
                        randomRoom = (rand() + cpt)% availableRoom.size();
                        random = rand() % 4;
                        cpt++;
                        // if (cpt > availableRoom.size())
                        //         cpt = 0;
                }
                availableRoom.push_back(i);
                cpt = 0;
        }
}

/*
** DEBBUG FUNCTION
*/
void Floor::printMaze(void)
{
        std::cout << "Floor " << _number << " = " << std::endl;
        for (int i = 0; i < _nbRoom; i++) {
                _roomMapping[i]->displayConnection();
        }
}

void Floor::setCurrentRoom(int currentRoom) {
        _currentRoom = currentRoom;
}

int Floor::getCurrentRoom(void) const {
        return _currentRoom;
}

DungeonRoom *Floor::getCurrentRoomObj(void) {
        return _roomMapping[this->getCurrentRoom()];
}

OtterEngine::Engine *Floor::getOe(void) {
        return _oe;
}

Dungeon *Floor::getDungeon(void) {
        return _dj;
}
