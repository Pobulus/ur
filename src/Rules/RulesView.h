/** @file */
#pragma once
#pragma once

#include "../Settings/Config.h"
#include "../MVC/View.h"
#include "RulesModel.h"
#include <vector>

class RulesView : public View {
    std::shared_ptr<RulesModel> model;
public:
    RulesView(std::shared_ptr<RulesModel> model) : model(model) {}

    virtual ~RulesView() {};

    virtual void show(sf::RenderTarget &target) {
        target.clear(Config::getInstance().getColor("background"));
        for (auto d: model->getContent()) {
            target.draw(*d);
        }
    }

};
