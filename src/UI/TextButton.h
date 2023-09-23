/** @file */
#pragma once

#include <cmath>
#include "Button.h"
//klasa przycisku

class TextButton : public Button {
    sf::Text textsprite;
    sf::Font font;
    sf::Sprite background;
    sf::RenderTexture renderTexture;
public:
    TextButton(sf::String text, sf::Vector2f size, std::string texturename, sf::Vector2f position, ClickEventType type)
            : Button(texturename, position, type) {
        body.setScale({1, 1});
        renderTexture.create(size.x, size.y);
        body.setTexture(renderTexture.getTexture(), true);

        font.loadFromFile("Resources/Roboto-Regular.ttf");
        textsprite.setFont(font);
        setText(text, 75.f);

        background.setTexture(texture);
        auto backgroundGlobalBounds = background.getGlobalBounds();

        background.setScale({size.x / backgroundGlobalBounds.width, size.y / backgroundGlobalBounds.height});

        backgroundGlobalBounds = background.getGlobalBounds();

        area = body.getGlobalBounds();
    }

    sf::Drawable *getDrawable() {
        renderTexture.clear(sf::Color::Transparent);
        background.setColor(Config::getInstance().getColor("tile"));
        textsprite.setFillColor(Config::getInstance().getColor("text"));
        renderTexture.draw(background);
        renderTexture.draw(textsprite);
        renderTexture.display();

        return &body;
    }

    void setText(sf::String text, float characterSize) {
        font = Config::getInstance().getFont();

        textsprite.setCharacterSize(characterSize);
        textsprite.setString(text);

        auto textGlobalBounds = textsprite.getGlobalBounds();
        auto bodyGlobalBounds = body.getGlobalBounds();


        auto center = sf::Vector2f(textsprite.getGlobalBounds().width, textsprite.getGlobalBounds().height) / 2.f;
        auto localBounds = center + sf::Vector2f(textsprite.getLocalBounds().left, textsprite.getLocalBounds().top);
        auto rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
        textsprite.setOrigin(rounded);
        textsprite.setPosition({bodyGlobalBounds.width / 2.f, bodyGlobalBounds.height / 2.f});
    }

};