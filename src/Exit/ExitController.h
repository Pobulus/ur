/** @file */
#pragma once

#include "ExitModel.h"
#include "../MVC/Controller.h"
#include <iostream>


class ExitController : public Controller {
    std::shared_ptr<MVC> menuMVC, selfMVC;

    std::shared_ptr<ExitModel> model;

    std::vector<std::shared_ptr<Clickable>> clickables;

public:

    ExitController(std::shared_ptr<ExitModel> model) : model(model) {
        clickables = model->getClickables();


    }

    virtual std::shared_ptr<MVC> handle(sf::Event event, sf::Vector2f mousePos) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto target: clickables) {
                auto clickEvent = target->click(mousePos);
                if (clickEvent != nullptr) {
                    switch (clickEvent->getType()) {
                        case menu:
                            std::cout << "Play" << std::endl;

                            return menuMVC;
                            break;

                        case quit:
                            std::cout << "QUIT" << std::endl;
                            return nullptr;
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

    void setMenu(std::shared_ptr<MVC> mvc) {
        menuMVC = mvc;
    }

    void setSelf(std::shared_ptr<MVC> mvc) {
        selfMVC = mvc;
    }

};