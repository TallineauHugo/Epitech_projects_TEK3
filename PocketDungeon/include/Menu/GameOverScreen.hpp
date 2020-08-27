#pragma once

#include "TextSprite.hpp"

class GameOverScreen {
public:
        GameOverScreen(OtterEngine::Engine *oe);
        ~GameOverScreen();
        void whileOnIt();
private:
        OtterEngine::TextSprite *_text;
        OtterEngine::TextSprite *_text2;
        OtterEngine::Engine *_oe;
};
