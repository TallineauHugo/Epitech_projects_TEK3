#pragma once

#include "Object.hpp"
#include "Dungeon.hpp"

class HUB;

class Portal : public OtterEngine::Object {
public:
        Portal(Vector2d, Vector2d, int dungeonLevel, OtterEngine::Engine *oe, HUB *hub);
        Dungeon *launchNewDungeon(void);
        bool collideVerification(OtterEngine::Engine *oe);
        int collideReaction(OtterEngine::Engine *oe);
        void updateEvents(OtterEngine::Engine *oe);
private:
        int _dungeonLevel;
        HUB *_hub;
        OtterEngine::Engine *_oe;
	std::vector<OtterEngine::Event<Portal>> _events;
};
