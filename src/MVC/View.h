/** @file */
#pragma once

#include <SFML/Graphics.hpp>


class View {
protected:

public:
    View() {}

    virtual ~View() {};

    virtual void show(sf::RenderTarget &target) = 0;

};