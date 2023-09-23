/** @file */
#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>


class Model {
public:
    Model() {}

    virtual ~Model() {};

    virtual std::vector<sf::Drawable *> getContent() = 0;

};
