/** @file */
#pragma once

#include "../MVC/Model.h"
#include "../UI/TextButton.h"
#include <iostream>

class MenuModel : public Model {
    std::vector<std::shared_ptr<Button>> buttons;
    sf::Sprite logo;
    sf::Texture logoTexture;
    std::shared_ptr<TextButton> playButton;

public:
    MenuModel() {
        logoTexture.loadFromFile("Resources/MenuLogo.png");
        logo.setTexture(logoTexture);
        logo.setScale({0.7f, 0.7f});
        logo.setPosition({110.f, 180.f});
        logo.setColor(Config::getInstance().getColor("tile"));
        buttons.push_back(std::make_shared<Button>("Resources/quit.png", sf::Vector2f(8.5 * 175.f, 50.f), quit));
        buttons.push_back(std::make_shared<Button>("Resources/settings.png", sf::Vector2f(50.f, 50.f), settings));
        playButton = std::make_shared<TextButton>("Play", sf::Vector2f(600.f, 150.f), "Resources/dicebg.png",
                                                  sf::Vector2f(530.f, 600.f), game);

    }

    virtual ~MenuModel() {};

    virtual std::vector<std::shared_ptr<Clickable>> getClickables() {
        std::vector<std::shared_ptr<Clickable>> out;
        for (auto b: buttons)
            out.push_back(b);
        out.push_back(playButton);

        return out;
    }

    virtual std::vector<sf::Drawable *> getContent() {
        std::vector<sf::Drawable *> out;

        for (auto b: buttons) {
            out.push_back(b->getDrawable());
        }
        playButton->setText(Config::getInstance().getTranslation("play"), 75.f);
        out.push_back(playButton->getDrawable());

        return out;
    }

    sf::Sprite getLogo() {
        logo.setColor(Config::getInstance().getColor("tile"));
        return logo;
    }


};
