/** @file */
#pragma once

#include "SettingsModel.h"

#include "../MVC/Controller.h"
#include <iostream>


class SettingsController : public Controller {
    std::shared_ptr<MVC> quitMVC, selfMVC;
    //ColorSetting colorSetting;

    std::shared_ptr<SettingsModel> model;
    int firstOrderRoll = -1;

    std::vector<std::shared_ptr<Clickable>> clickables;

public:

    SettingsController(std::shared_ptr<SettingsModel> model) : model(model) {
        clickables = model->getClickables();


    }

    virtual std::shared_ptr<MVC> handle(sf::Event event, sf::Vector2f mousePos) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto target: clickables) {
                auto clickEvent = target->click(mousePos);
                if (clickEvent != nullptr) {
                    switch (clickEvent->getType()) {
                        case color:
                            model->toggleColor();
                            break;
                        case language:
                            model->toggleLanguage();
                            break;
                        case sound:
                            model->toggleSound();
                            break;
                        case quit:
                            std::cout << "QUIT" << std::endl;
                            model->savePreferences();
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

    void setSelf(std::shared_ptr<MVC> mvc) {
        selfMVC = mvc;
    }

};