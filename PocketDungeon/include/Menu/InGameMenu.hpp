#pragma once

#include <vector>
#include "TextSprite.hpp"
#include "FixedSprite.hpp"
#include "MainMenu.hpp"

class InGameMenu {
public:
        InGameMenu(OtterEngine::Engine *oe);
        ~InGameMenu();
        void whileOnIt();
        void displayMenu();
        void modifyCursorPos();
        void quit();
        bool IsQuitTrue();
        std::string getName();


        void updateEvents(OtterEngine::Engine *oe);

	int DownReaction(OtterEngine::Engine *oe);
	int UpReaction(OtterEngine::Engine *oe);

	int EnterReaction(OtterEngine::Engine *oe);
        int NoEnterReaction(OtterEngine::Engine *oe);

        bool EnterVerification(OtterEngine::Engine *oe);
        bool NoEnterVerification(OtterEngine::Engine *oe);


	// int PauseReaction(OtterEngine::Engine *oe);
        // int NoPauseReaction(OtterEngine::Engine *oe);
        //
        // bool PauseVerification(OtterEngine::Engine *oe);
        // bool NoPauseVerification(OtterEngine::Engine *oe);

        int NoDownReaction(OtterEngine::Engine *oe);
	int NoUpReaction(OtterEngine::Engine *oe);

	bool UpVerification(OtterEngine::Engine *oe);
	bool DownVerification(OtterEngine::Engine *oe);

	bool NoUpVerification(OtterEngine::Engine *oe);
	bool NoDownVerification(OtterEngine::Engine *oe);
private:
        Menus _actualMenu;
        OtterEngine::FixedSprite *_bgMenu;
        std::vector<OtterEngine::TextSprite*> _textList;
        int _cursorPos;
        OtterEngine::TextSprite *_cursor;
	std::vector<OtterEngine::Event<InGameMenu>> _events;
        std::vector<int> _cursorY;
        bool _quit;
        OtterEngine::Engine *_oe;
};
