/** @file */
#pragma once

#include "../UI/Highlightable.h"
#include "../UI/Drawable.h"

class Player;

class Piece : public Highlightable, public Drawable {
    std::string colorname;
    sf::Sprite body;
    sf::Color color;
    Player *owner;
    std::vector<int> path;

    int progress = 0;

    //Ustawia kolor pionka zgodnie z jego stanem (podświetlony lub nie)
    void updateColor() {

    }

public:

    //Pionek przyjmuje w konstruktorze nazwę koloru w Config, który ma przyjąć
    Piece(std::string colorname, Player *owner, std::vector<int> path) : colorname(colorname), owner(owner),
                                                                         path(path) {
        body.setScale({0.2, 0.2});
        body.setColor(Config::getInstance().getColor(colorname));
    }

    int getTargetTileIndex(int hops) {
        if (progress + hops < path.size()) {
            return path[progress + hops];
        }
        return -1;
    }

    void setProgress(int p) {
        if (p > 0 and p < path.size())
            progress = p;

    }

    int getProgress() {
        return progress;
    }

    void setTexture(sf::Texture &t) { body.setTexture(t); }

    sf::Drawable *getDrawable() {
        if (highlighted) {
            body.setColor(Config::getInstance().getColor("selected"));
        } else {
            body.setColor(Config::getInstance().getColor(colorname));
        }
        updateColor();
        return &body;
    }

    void advance(int hops) {
        progress += hops;
    }

    void retreat() {
        progress = 0;
    }

    Player *getOwner() {
        return owner;
    }

    void setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
    }

    virtual void highlight(bool state) {
        highlighted = state;
        std::cout << "\nh" << highlighted;


    }

};