#pragma once

#include "Object.hpp"
#include "Floor.hpp"

class Door : public OtterEngine::Object {
public:
        Door(Vector2d pos, int direction, Floor *floor);
        bool collideVerification(OtterEngine::Engine *oe);
        int collideReaction(OtterEngine::Engine *oe);
        void updateEvents(OtterEngine::Engine *oe);
private:
        int _direction;
        Floor *_floor;
	std::vector<OtterEngine::Event<Door>> _events;
};
