/** @file */
#pragma once

#include "../Settings/Config.h"
#include "../MVC/View.h"
#include "ExitModel.h"
#include <vector>

class ExitView : public View {
    std::shared_ptr<ExitModel> model;
public:
    ExitView(std::shared_ptr<ExitModel> model) : model(model) {}

    virtual ~ExitView() {};

    virtual void show(sf::RenderTarget &target) {
        target.clear(Config::getInstance().getColor("background"));
        for (auto d: model->getContent()) {
            target.draw(*d);
        }
    }

};
