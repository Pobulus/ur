/** @file */
#pragma once

#include "../Settings/Config.h"
#include "../MVC/View.h"
#include "SettingsModel.h"
#include <vector>

class SettingsView : public View {
    std::shared_ptr<SettingsModel> model;
public:
    SettingsView(std::shared_ptr<SettingsModel> model) : model(model) {}

    virtual ~SettingsView() {};

    virtual void show(sf::RenderTarget &target) {
        target.clear(Config::getInstance().getColor("background"));
        for (auto d: model->getContent()) {
            target.draw(*d);
        }
    }

};
