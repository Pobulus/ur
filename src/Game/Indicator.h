/** @file */
#pragma once

#include "../UI/Drawable.h"

enum phaseType {
    ROLL, MOVE
};

class Indicator : public Drawable {
    sf::Sprite icon, background, crown;
    sf::Texture move, roll, crownTexture, backgroundTexture;
    sf::Sprite body;
    sf::RenderTexture renderTexture;
    bool crownVisible = false;
public:
    Indicator() {
        renderTexture.create(800.f, 800.f);
        body.setTexture(renderTexture.getTexture(), true);
        body.setPosition({150.f, 775.f});
        body.setScale({0.172f, 0.172f});

        crownTexture.loadFromFile("Resources/crown.png");
        crown.setTexture(crownTexture);

        backgroundTexture.loadFromFile("Resources/tile.png");
        background.setTexture(backgroundTexture);

        move.loadFromFile("Resources/playerIcon.png");
        roll.loadFromFile("Resources/diceIcon.png");

    }

    sf::Drawable *getDrawable() {
        renderTexture.clear(sf::Color::Transparent);
        background.setColor(Config::getInstance().getColor("tile"));
        renderTexture.draw(background);
        renderTexture.draw(icon);
        if (crownVisible)renderTexture.draw(crown);
        renderTexture.display();
        return &body;
    }

    void setIconColor(sf::Color color) {

        icon.setColor(color);
    }

    void showCrown() {
        crownVisible = true;
    }

    void hideCrown() {
        crownVisible = false;
    }

    void setPhase(phaseType phase) {
        switch (phase) {
            case ROLL:
                icon.setTexture(roll);
                break;
            case MOVE:
                icon.setTexture(move);
                break;
        }
    }
};
