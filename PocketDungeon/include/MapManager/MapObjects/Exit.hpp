#pragma once

#include "Object.hpp"

class Dungeon;

class Exit : public OtterEngine::Object {
public:
        Exit(Vector2d, Dungeon *);
        void useExit(void);
        int collideReaction(OtterEngine::Engine *oe);
        bool collideVerification(OtterEngine::Engine *oe);
        void updateEvents(OtterEngine::Engine *oe);

private:
        Dungeon *_dungeon;
	std::vector<OtterEngine::Event<Exit>> _events;
};
