/** @file */
#pragma once

#include "RulesModel.h"
#include "../MVC/Controller.h"
#include <iostream>


class RulesController : public Controller {
    std::shared_ptr<MVC> quitMVC, rulesMVC, selfMVC;

    std::shared_ptr<RulesModel> model;

    std::vector<std::shared_ptr<Clickable>> clickables;
public:

    RulesController(std::shared_ptr<RulesModel> model) : model(model) {
        clickables = model->getClickables();

    }

    virtual std::shared_ptr<MVC> handle(sf::Event event, sf::Vector2f mousePos) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto target: clickables) {
                auto clickEvent = target->click(mousePos);
                if (clickEvent != nullptr) {
                    switch (clickEvent->getType()) {
                        case quit:
                            return quitMVC;
                            break;
                        case goLeft:
                            model->switchToLeft();
                            clickables = model->getClickables();
                            break;
                        case goRight:
                            model->switchToRight();
                            clickables = model->getClickables();
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

    void setSelf(std::shared_ptr<MVC> mvc) {
        selfMVC = mvc;
    }

};