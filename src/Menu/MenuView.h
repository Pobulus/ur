/** @file */
#pragma once

#include "../Settings/Config.h"
#include "../MVC/View.h"
#include "MenuModel.h"
#include <vector>

class MenuView : public View {
    std::shared_ptr<MenuModel> model;
    float animateLogo = 500;
public:
    MenuView(std::shared_ptr<MenuModel> model) : model(model) {}

    virtual ~MenuView() {};

    virtual void show(sf::RenderTarget &target) {
        target.clear(Config::getInstance().getColor("background"));
        auto logo = model->getLogo();
        if (animateLogo > 0) { //animacja
            logo.move({0.f, -animateLogo});
            animateLogo -= 1.0;
            if (animateLogo <= 0.0) {
                JukeBox::getInstance().playPiece();
            }
        }

        target.draw(logo);
        for (auto d: model->getContent()) {
            target.draw(*d);
        }
    }

};
