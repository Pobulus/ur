/** @file */
#pragma once

#include "../Settings/Config.h"
#include "../MVC/View.h"
#include "GameModel.h"
#include <vector>

class GameView : public View {
    std::shared_ptr<GameModel> model;
public:
    GameView(std::shared_ptr<GameModel> model) : model(model) {}

    virtual ~GameView() {};

    virtual void show(sf::RenderTarget &target) {
        target.clear(Config::getInstance().getColor("background"));
        auto dice = model->getDice();
        if (model->doRollAnimation()) {
            sf::sleep(sf::milliseconds(50));
            std::cout << "Rolled";
            dice.roll();


        }
        target.draw(*dice.getDrawable());
        for (auto d: model->getContent()) {
            target.draw(*d);
        }
    }

};
