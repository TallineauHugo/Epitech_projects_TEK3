#pragma once

#include "MapManager.hpp"
#include "HUB.hpp"

class HUBFactory : public MapManager {
public:
        static HUBFactory *getInstance() {
                static HUBFactory instance;
                return &instance;
        }
        HUB *createHUB(OtterEngine::Engine *oe);
        ~HUBFactory();
private:
        HUBFactory();
private:
        HUB *_HUB;
};
