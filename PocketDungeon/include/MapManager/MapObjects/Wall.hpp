#pragma once

#include "Object.hpp"

class Wall : public virtual OtterEngine::Object {
public:
        Wall(Vector2d pos, Vector2d size);
        ~Wall() {}

        void updateEvents(OtterEngine::Engine *oe);
        int collideReaction(OtterEngine::Engine *oe);
        bool collideVerification(OtterEngine::Engine *oe);
	std::vector<OtterEngine::Event<Wall>> _events;
};
