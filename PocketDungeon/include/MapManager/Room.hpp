#pragma once

#include "Object.hpp"
#include <string>

class Room : public virtual OtterEngine::Object {
public:
        Room(std::string name, int level);
        Room(std::string name);
        ~Room();
        std::string getName(void) const;
protected:
        int _level;
        std::string _name;
};
