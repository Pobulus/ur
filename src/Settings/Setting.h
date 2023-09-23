/** @file */
#pragma once

#include "Config.h"

class Setting {
    std::vector<std::string> options;
    int current = 0;
public:
    Setting() {

    }

    void toggle() {
        current++;
        if (current == options.size()) {
            current = 0;
        }
    }

    void setCurrent(int value) {
        if (value >= options.size()) {
            current = 0;
        } else {
            current = value;
        }

    }

    int getCurrent() const {
        return current;
    }

    void setOptions(std::vector<std::string> opt) {
        options = opt;
    }

    std::string getName() const {
        return options[current];
    }
};