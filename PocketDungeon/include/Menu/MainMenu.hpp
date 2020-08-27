#pragma once

#include <vector>
#include "TextSprite.hpp"

enum Menus {
        MAIN,
        PLAY,
        OPTION
};

class MainMenu {
public:
        MainMenu(OtterEngine::Engine *oe);
        ~MainMenu();
        void whileOnIt();
        void displayMenu();
        void modifyCursorPos();
        void quit();
        bool IsQuitTrue();


        void updateEvents(OtterEngine::Engine *oe);

	int DownReaction(OtterEngine::Engine *oe);
	int UpReaction(OtterEngine::Engine *oe);

	int EnterReaction(OtterEngine::Engine *oe);
        int NoEnterReaction(OtterEngine::Engine *oe);

        bool EnterVerification(OtterEngine::Engine *oe);
        bool NoEnterVerification(OtterEngine::Engine *oe);

        int NoDownReaction(OtterEngine::Engine *oe);
	int NoUpReaction(OtterEngine::Engine *oe);

	bool UpVerification(OtterEngine::Engine *oe);
	bool DownVerification(OtterEngine::Engine *oe);

	bool NoUpVerification(OtterEngine::Engine *oe);
	bool NoDownVerification(OtterEngine::Engine *oe);
private:
        Menus _actualMenu;
        std::vector<OtterEngine::TextSprite*> _textList;
        int _cursorPos;
        OtterEngine::TextSprite *_cursor;
	std::vector<OtterEngine::Event<MainMenu>> _events;
        std::vector<int> _cursorY;
        bool _quit;
        OtterEngine::Engine *_oe;
        // int _cursorY[3];
};
