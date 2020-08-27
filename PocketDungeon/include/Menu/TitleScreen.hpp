#pragma once

#include "TextSprite.hpp"

class TitleScreen {
public:
        TitleScreen(OtterEngine::Engine *oe);
        ~TitleScreen();
        void whileOnIt();
private:
        OtterEngine::TextSprite *_text;
        OtterEngine::Engine *_oe;
};
