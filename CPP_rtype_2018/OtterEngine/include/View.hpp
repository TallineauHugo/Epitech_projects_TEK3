#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include "define.hpp"

class OtterEngine::View {
public:
        static View *getInstance(sf::Vector2f pos, sf::Vector2f size) {
                static View instance(pos, size);
                return &instance;
        }
        ~View();
        void setPosition(const sf::Vector2f pos);
        sf::Vector2f getPosition(void) const;
        void setSize(const sf::Vector2f size);
        sf::Vector2f getSize(void) const;
        sf::View *getView(void) const;
private:
        View(sf::Vector2f pos, sf::Vector2f size);
private:
        sf::View *_view;
        sf::Vector2f _pos;
        sf::Vector2f _size;
};
