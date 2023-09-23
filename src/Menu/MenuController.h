/** @file */
#pragma once

#include "MenuModel.h"
#include "../MVC/Controller.h"
#include <iostream>


class MenuController : public Controller {
    std::shared_ptr<MVC> quitMVC, gameMVC, selfMVC, settingsMVC;

    std::shared_ptr<MenuModel> model;

    std::vector<std::shared_ptr<Clickable>> clickables;

public:

    MenuController(std::shared_ptr<MenuModel> model) : model(model) {
        clickables = model->getClickables();


    }

    virtual std::shared_ptr<MVC> handle(sf::Event event, sf::Vector2f mousePos) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto target: clickables) {
                auto clickEvent = target->click(mousePos);
                if (clickEvent != nullptr) {
                    switch (clickEvent->getType()) {
                        case game:
                            std::cout << "Play" << std::endl;

                            return gameMVC;
                            break;
                        case settings:
                            return settingsMVC;
                            break;
                        case quit:
                            std::cout << "QUIT" << std::endl;
                            return quitMVC;
                            break;

                    }
                }
            }

        } else {
            for (auto target: clickables) { //najechanie kursorem
                target->hover(mousePos);

            }

        }


        return selfMVC;
    }

    void setQuit(std::shared_ptr<MVC> mvc) {
        quitMVC = mvc;
    }

    void setGame(std::shared_ptr<MVC> mvc) {
        gameMVC = mvc;
    }

    void setSettings(std::shared_ptr<MVC> mvc) {
        settingsMVC = mvc;
    }

    void setSelf(std::shared_ptr<MVC> mvc) {
        selfMVC = mvc;
    }

};