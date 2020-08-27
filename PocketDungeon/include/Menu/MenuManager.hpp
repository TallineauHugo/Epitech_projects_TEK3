#pragma once

#include "MainMenu.hpp"
#include "TitleScreen.hpp"
#include "InGameMenu.hpp"
#include "GameOverScreen.hpp"

class MenuManager {
public:
        static MenuManager *getInstance() {
		static MenuManager instance;

		return &instance;
        }
        ~MenuManager() {}
        TitleScreen *getTitleScreenInstance(OtterEngine::Engine *oe) {
                return new TitleScreen(oe);
        }
        MainMenu *getMainMenuInstance(OtterEngine::Engine *oe) {
                return new MainMenu(oe);
        }
        InGameMenu *getInGameMenuInstance(OtterEngine::Engine *oe) {
                return new InGameMenu(oe);
        }
        GameOverScreen *getGameOverScreenInstance(OtterEngine::Engine *oe) {
                return new GameOverScreen(oe);
        }
private:
        MenuManager() {}
};
