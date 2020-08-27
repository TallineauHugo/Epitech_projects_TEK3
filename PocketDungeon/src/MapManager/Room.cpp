#include <iostream>
#include <cstdlib>
#include "time.h"
#include "Room.hpp"

Room::Room(std::string name, int level) : _level(level), _name(name) {}

Room::Room(std::string name) : _level(0), _name(name) {}

Room::~Room() {
        /*
        ** DEBBUG
        */
}

std::string Room::getName(void) const {
        return _name;
}
