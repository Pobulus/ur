/** @file */
#pragma once

#include <SFML/Graphics.hpp>
#include "../Settings/Config.h"
#include "Drawable.h"
#include "Clickable.h"
#include "JukeBox.h"
//klasa przycisku

class Button : public Clickable, public ::Drawable, public Highlightable {
protected:
    sf::Texture texture;
    sf::Sprite body;
    ClickEventType type;
public:
    Button(std::string texturename, sf::Vector2f position, ClickEventType type) : type(type) {
        texture.loadFromFile(texturename);
        body.setTexture(texture);
        body.setScale({0.15f, 0.15f});
        body.setPosition(position);
        area = body.getGlobalBounds();
    }

    virtual sf::Drawable *getDrawable() {
        //body.setColor(Config::getInstance().getColor("tile"));
        return &body;
    }

    std::shared_ptr<ClickEvent> click(sf::Vector2f position) {
        if (area.contains(position)) {
            JukeBox::getInstance().playButton();
            return std::make_shared<ClickEvent>(type);

        }
        return nullptr;
    };

    std::shared_ptr<ClickEvent> hover(sf::Vector2f position) {

        if (area.contains(position))
            highlight(1);
        else
            highlight(0);
        return nullptr;
    }

    virtual void highlight(bool state) {
        highlighted = state;

        if (highlighted) {
            body.setColor(Config::getInstance().getColor("selected"));
        } else {
            body.setColor(Config::getInstance().getColor("tile"));
        }

    }

};