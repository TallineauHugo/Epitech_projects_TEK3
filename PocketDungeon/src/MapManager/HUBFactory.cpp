#include "HUBFactory.hpp"
#include "OtterEngine.hpp"
#include <iostream>

HUBFactory::HUBFactory()
{
}

HUBFactory::~HUBFactory() {}

HUB *HUBFactory::createHUB(OtterEngine::Engine *oe) {
        HUB *hub = HUB::getInstance(oe);
        hub->loadHUB();
        return hub;
}
