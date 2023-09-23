/** @file */
#pragma once

#include "Model.h"
#include "View.h"
#include "Controller.h"

struct MVC {
    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
    std::shared_ptr<Controller> controller;
};