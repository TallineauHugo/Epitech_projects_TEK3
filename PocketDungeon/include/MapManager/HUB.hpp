#pragma once

#include <vector>
#include "Room.hpp"
#include "OtterEngine.hpp"

class HUB : public Room {
public:
        static HUB *getInstance(OtterEngine::Engine *oe) {
		static HUB instance(oe);

		return &instance;
	}
        ~HUB();
        void clearHUB();
        void loadHUB();
private:
        HUB(OtterEngine::Engine *oe);
        OtterEngine::Engine *_oe;
};
