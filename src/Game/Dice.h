/** @file */
#pragma once

#include <random>
#include "../UI/Clickable.h"
#include "../UI/Drawable.h"
#include "../UI/Highlightable.h"

class Dice : public Clickable, public ::Drawable, public Highlightable {
    short int state = 0;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
    std::vector<sf::Sprite> dots;
    sf::Sprite background;
    sf::Sprite body;
    sf::RenderTexture texture;
    sf::Texture dotTexture, bgTexture;
public:
    Dice(const Dice &d) : rd(), gen(rd()) {
        dots = d.dots;
        background = d.background;


        distr = d.distr;
        state = d.state;
        body = d.body;
        texture.create(500.f, 175.f);
        dotTexture = d.dotTexture;
        bgTexture = d.bgTexture;
        body.setTexture(texture.getTexture());
        area = body.getGlobalBounds();

    }

    Dice() : gen(rd()), distr(0, 15) {
        dotTexture.loadFromFile("Resources/tile.png");
        //tło kostki
        bgTexture.loadFromFile("Resources/dicebg.png");

        texture.create(500.f, 175.f);

        for (int i = 0; i < 4; i++) {
            sf::Sprite dot;
            dot.setTexture(dotTexture);
            dot.setScale(0.1, 0.1);
            dot.setPosition({45.f + i * 90, 30.f});
            dots.push_back(dot);

        }
        body.setTexture(texture.getTexture());

        body.setPosition({1050.f, 775.f});
        background.setTexture(bgTexture);
        background.setScale(1, 0.8); //zmniejsz wysokość do 80%
        area = body.getGlobalBounds();
    }

    int roll() {
        state = distr(gen);
        std::cout << state << std::endl;
        return state;
    }

    std::shared_ptr<ClickEvent> click(sf::Vector2f position) {
        if (area.contains(position))
            return std::make_shared<ClickEvent>(dice);
        return nullptr;
    };

    void clear() {
        state = 0;
    }

    int getState() const {
        return state;
    }

    void setState(int s) {
        if (s > 0 and s < 16)
            state = s;

    }

    int getValue() const {
        int temp = state;
        int count = 0;
        while (temp) {
            count += temp & 1;
            temp >>= 1;
        }
        return count;
    }

    sf::Drawable *getDrawable() {
        //background.setColor(Config::getInstance().getColor("tile"));
        texture.draw(background);
        for (int i = 0; i < 4; i++) {
            auto color = (((state >> i) & 1) ?
                          Config::getInstance().getColor("background") :
                          Config::getInstance().getColor("tile"));
            dots[i].setColor(color);
            texture.draw(dots[i]);
        }
        texture.display();
        return &body;
    }

    std::shared_ptr<ClickEvent> hover(sf::Vector2f position) {

        if (area.contains(position))

            return std::make_shared<ClickEvent>(dice);

        return nullptr;
    }

    void highlightForbidden() {
        background.setColor(Config::getInstance().getColor("forbidden"));
    }

    virtual void highlight(bool state) {
        highlighted = state;

        if (highlighted) {
            background.setColor(Config::getInstance().getColor("selected"));
        } else {
            background.setColor(Config::getInstance().getColor("tile"));
        }


    }
};