/** @file */
#pragma once

class Highlightable {
protected:
    bool highlighted = false;
public:
    Highlightable() {

    }

    virtual ~Highlightable() {}

    virtual void highlight(bool state) = 0;

    bool isHighlighted() {
        return highlighted;
    }
};