/** @file */
#pragma once

#include <SFML/Graphics.hpp>

enum ClickEventType {
    board, quit, reset, help, dice, game, settings, menu, language, color, sound, goLeft, goRight
};

class ClickEvent {
protected:
    ClickEventType type;
    sf::Vector2i position = {0, 0};
public:

    ClickEvent(ClickEventType type) : type(type) {}

    ClickEventType getType() {
        return type;
    }

    sf::Vector2i getPosition() {
        return position;
    }
};

class Clickable {
protected:
    sf::FloatRect area;

public:
    Clickable() {}

    virtual ~Clickable() {}

    virtual std::shared_ptr<ClickEvent> click(sf::Vector2f position) = 0;

    virtual std::shared_ptr<ClickEvent> hover(sf::Vector2f position) = 0;

};


class BoardClicked : public ClickEvent {

public:
    BoardClicked(sf::Vector2i pos) : ClickEvent(board) {
        position = pos;
    }

};
