/** @file */
#pragma once

#include "../MVC/Model.h"
#include "../UI/TextButton.h"
#include <iostream>

class ExitModel : public Model {
    std::vector<std::shared_ptr<Button>> buttons;

    std::shared_ptr<TextButton> yesButton, noButton;
    sf::Text title;
    sf::Font font;
public:
    ExitModel() {
        font.loadFromFile("Resources/Cuneiform.ttf");
        title.setFont(font);
        title.setCharacterSize(200.f);
        title.setPosition({200.f, 200.f});
        yesButton = std::make_shared<TextButton>("Yes", sf::Vector2f(300.f, 150.f), "Resources/dicebg.png",
                                                 sf::Vector2f(450.f, 700.f), quit);
        noButton = std::make_shared<TextButton>("No", sf::Vector2f(300.f, 150.f), "Resources/dicebg.png",
                                                sf::Vector2f(910.f, 700.f), menu);

    }

    virtual ~ExitModel() {};

    void setTitle() {
        font = Config::getInstance().getFont();
        title.setString(Config::getInstance().getTranslation("quitPrompt"));
        title.setFillColor(Config::getInstance().getColor("tile"));

        auto textGlobalBounds = title.getGlobalBounds();
        auto center = sf::Vector2f(title.getGlobalBounds().width, title.getGlobalBounds().height) / 2.f;
        auto localBounds = center + sf::Vector2f(title.getLocalBounds().left, title.getLocalBounds().top);
        auto rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
        title.setOrigin(rounded);
        title.setPosition({830.f, 200.f});
    }

    virtual std::vector<std::shared_ptr<Clickable>> getClickables() {
        std::vector<std::shared_ptr<Clickable>> out;
        out.push_back(yesButton);
        out.push_back(noButton);


        return out;
    }

    virtual std::vector<sf::Drawable *> getContent() {
        std::vector<sf::Drawable *> out;
        setTitle();
        out.push_back(&title);
        yesButton->setText(Config::getInstance().getTranslation("yes"), 75.f);
        noButton->setText(Config::getInstance().getTranslation("no"), 75.f);
        out.push_back(yesButton->getDrawable());
        out.push_back(noButton->getDrawable());


        return out;
    }


};
