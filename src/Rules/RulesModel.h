/** @file */
#pragma once
#pragma once

#include "../MVC/Model.h"
#include <regex>
#include <filesystem>
#include <iostream>
#include "../UI/Button.h"
#include "../UI/TextButton.h"

class RulesModel : public Model {


    std::shared_ptr<Button> button, leftButton, rightButton;
    std::shared_ptr<TextButton> textButton;
    std::vector<sf::Texture> pages;
    sf::Sprite image;
    int currentPage = 0;
public:
    RulesModel() {
        button = std::make_shared<Button>("Resources/quit.png", sf::Vector2f(8.5 * 175.f, 50.f), quit);
        leftButton = std::make_shared<Button>("Resources/goLeft.png", sf::Vector2f(83.f, 420.f), goLeft);
        rightButton = std::make_shared<Button>("Resources/goRight.png", sf::Vector2f(1457.f, 420.f), goRight);

        const std::regex rulePage("rule[0-9]+\\.png");
        for (const auto &file: std::filesystem::recursive_directory_iterator("Resources/")) {
            if (std::regex_match(file.path().filename().u8string(), rulePage)) {
                sf::Texture temp;
                temp.loadFromFile(file.path().u8string());

                pages.push_back(temp);
                std::cout << file.path().u8string() << std::endl;
            }
        }
        if (pages.size())image.setTexture(pages[0]);

        image.setPosition(207.f, 100.f);
        image.setScale({0.75f, 0.75f});
    }

    virtual ~RulesModel() {};

    virtual std::vector<std::shared_ptr<Clickable>> getClickables() {
        std::vector<std::shared_ptr<Clickable>> out;
        out.push_back(button);
        if (currentPage != 0)
            out.push_back(leftButton);
        if (currentPage < pages.size() - 1)
            out.push_back(rightButton);


        return out;
    }

    virtual std::vector<sf::Drawable *> getContent() {
        std::vector<sf::Drawable *> out;


        out.push_back(button->getDrawable());
        if (currentPage != 0)
            out.push_back(leftButton->getDrawable());
        if (currentPage < pages.size() - 1)
            out.push_back(rightButton->getDrawable());
        out.push_back(&image);
        //out.push_back(textButton->getDrawable());


        return out;
    }

    void switchToLeft() {
        if (currentPage > 0)currentPage--;
        image.setTexture(pages[currentPage], true);
    }

    void switchToRight() {
        if (currentPage < pages.size() - 1)currentPage++;
        image.setTexture(pages[currentPage], true);
    }

};
