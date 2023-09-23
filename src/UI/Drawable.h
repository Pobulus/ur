/** @file */
#pragma once

#include <SFML/Graphics.hpp>

class Drawable {
public:
    virtual ~Drawable() {}

    virtual sf::Drawable *getDrawable() = 0;
};