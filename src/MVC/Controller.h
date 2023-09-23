/** @file */
#pragma once

#include <SFML/Graphics.hpp>

struct MVC;

class Controller {


public:

    Controller() {}

    virtual ~Controller() {}

    virtual std::shared_ptr<MVC> handle(sf::Event event, sf::Vector2f mousePos) = 0;

};
