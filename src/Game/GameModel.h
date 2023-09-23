/** @file */
#pragma once

#include "../MVC/Model.h"
#include "Tile.h"
#include "Indicator.h"
#include <iostream>
#include "GameState.h"


class GameModel : public Model {
    std::shared_ptr<Piece> selected = nullptr;
    std::shared_ptr<Tile> selectedTile = nullptr;
    std::vector<std::shared_ptr<Button>> buttons;
    int rollAnimation = 0;
    Indicator indicator;
public:
    GameModel() {
        buttons.push_back(std::make_shared<Button>("Resources/quit.png", sf::Vector2f(8.5 * 175.f, 50.f), quit));
        buttons.push_back(std::make_shared<Button>("Resources/reset.png", sf::Vector2f(50.f, 50.f), reset));
        buttons.push_back(std::make_shared<Button>("Resources/help.png", sf::Vector2f(25.f + 175.f, 50.f), help));
    }

    virtual ~GameModel() {};

    virtual std::vector<std::shared_ptr<Clickable>> getClickables() {
        std::vector<std::shared_ptr<Clickable>> out;
        for (auto b: buttons)
            out.push_back(b);
        out.push_back(GameState::getInstance().getDice());
        out.push_back(GameState::getInstance().getBoard());

        return out;
    }

    virtual std::vector<sf::Drawable *> getContent() {
        std::vector<sf::Drawable *> out;
        for (auto t: GameState::getInstance().getBoard()->getTiles()) {
            out.push_back(t->getDrawable());
        }
        for (auto b: buttons) {
            out.push_back(b->getDrawable());
        }
        //Pionki wyrysowane jako część tile
        indicator.setPhase(GameState::getInstance().getRolled() ? MOVE : ROLL);

        sf::Color color = Config::getInstance().getColor(GameState::getInstance().getPlayers().first->getPlayername());
        indicator.setIconColor(color);
        if (GameState::getInstance().getFinished())
            indicator.showCrown();
        else
            indicator.hideCrown();
        out.push_back(indicator.getDrawable());
        return out;
    }

    void endgame(bool state) {
        if (state) {
            indicator.showCrown();
        } else {
            indicator.hideCrown();
        }
    }

    void updateTiles() {
        for (auto t: GameState::getInstance().getBoard()->getTiles()) {
            t->display();
        }
    }

    void setupRollAnimation() {
        rollAnimation = 10;
    }

    bool rollAnimationInProgress() const {
        return rollAnimation;
    }

    bool doRollAnimation() {
        if (rollAnimation > 0) {
            rollAnimation--;
        }
        return rollAnimation;
    }

    Dice getDice() {
        Dice dice = *GameState::getInstance().getDice(); //skopiuj
        return dice;
    }


};
