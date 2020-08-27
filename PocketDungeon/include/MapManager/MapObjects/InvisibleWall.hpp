#pragma once

#include "Wall.hpp"

class InvisibleWall : public Wall {
public:
        InvisibleWall(Vector2d pos, Vector2d size);

        ~InvisibleWall() {}
};
