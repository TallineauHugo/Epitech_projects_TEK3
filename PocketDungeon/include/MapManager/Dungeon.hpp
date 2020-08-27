#pragma once

#include <vector>
#include "MapManager.hpp"
#include "OtterEngine.hpp"
#include "Theme.hpp"
#include "Floor.hpp"
#include "HUBFactory.hpp"
#include "Theme.hpp"

class Dungeon {
public:

        Dungeon(int level, OtterEngine::Engine*);
        ~Dungeon();
        void setCurrentFloor(int);
        int getCurrentFloor(void) const;
        void goToNextFloor(void);
        void enterCurrentFloor(void);
        void ExitDungeon(void);
        // void loadDungeon(void);
private:
        std::vector<Floor*> _floorList;
        OtterEngine::Engine *_oe;
        Theme _theme;
	OtterEngine::FixedSprite *_themeSprite;
        int _level;
        int _nbFloor;
        int _currentFloor;
        bool _ended;
};
