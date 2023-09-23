/** @file */
#pragma once

#include "Tile.h"
#include "GameModel.h"
#include "../MVC/Controller.h"
#include <iostream>
#include "../UI/JukeBox.h"

class GameController : public Controller {
    std::shared_ptr<MVC> quitMVC, rulesMVC, selfMVC;

    std::shared_ptr<GameModel> model;
    int firstOrderRoll = -1;

    std::vector<std::shared_ptr<Clickable>> clickables;

public:

    GameController(std::shared_ptr<GameModel> model) : model(model) {
        clickables = model->getClickables();
        if (GameState::getInstance().getRolled())checkValidMoves();

    }

    //zwraca true jeśli są dostępne ruchy
    bool checkValidMoves() {

        int rolledValue = GameState::getInstance().getDice()->getValue();
        auto board = GameState::getInstance().getBoard();
        if (rolledValue == 0) return false; // jeśli wylosowano 0, nie można się ruszyć
        auto players = GameState::getInstance().getPlayers();
        bool output = false;
        for (auto piece: players.first->getPieces()) {
            std::cout << "piece" << std::endl;
            output = output + checkValidMove(piece, rolledValue);
        }
        model->updateTiles();
        std::cout << "check valid moves" << output << std::endl;
        return output;
    }

    bool checkValidMove(std::shared_ptr<Piece> piece, int rolledValue) {
        std::cout << "checking" << std::endl;
        auto targetTile = GameState::getInstance().getBoard()->getTile(piece->getTargetTileIndex(rolledValue));
        if (targetTile != nullptr) {
            if (targetTile->getType() == empty) {//na polach startowych i końcowych, pionki mogą leżeć na sobie

                piece->highlight(1);
                return true;
            } else {
                auto occupant = targetTile->getPiece();
                if (occupant == nullptr) { //jeśli pole jest puste
                    piece->highlight(1);
                    return true;
                }
                    //jeśli pionek można zbić
                else if (occupant->getOwner() != piece->getOwner() and targetTile->getType() == normal) {
                    piece->highlight(1);
                    return true;
                }
            }
        }
        return false;
    }

    bool rollDice() {
        if (!GameState::getInstance().getRolled()) {

            GameState::getInstance().getDice()->roll();
            GameState::getInstance().setRolled(true);
            JukeBox::getInstance().playDice();
            model->setupRollAnimation();
            return true;
        }
        return false;
    }

    void handleBoard(std::shared_ptr<ClickEvent> clickEvent) {
        if (GameState::getInstance().getStarted() and GameState::getInstance().getRolled()) {
            std::shared_ptr<Player> currentPlayer = GameState::getInstance().getPlayers().first;
            std::cout << "dice was rolled" << std::endl;
            sf::Vector2i tileCoordinates = clickEvent->getPosition();
            auto selectedTile = GameState::getInstance().getBoard()->getTile(tileCoordinates);
            // jeśli wybrane pole zawiera pionek obecnego gracza
            auto piece = selectedTile->getPiece();
            if (piece != nullptr and piece->getOwner() == currentPlayer.get()) {
                std::cout << "you are the owner" << std::endl;
                auto board = GameState::getInstance().getBoard();
                int rolledValue = GameState::getInstance().getDice()->getValue();
                if (checkValidMove(piece, rolledValue)) {

                    auto targetTile = board->getTile(piece->getTargetTileIndex(rolledValue));
                    if (targetTile->getType() == normal) { //zbijanie pionków
                        auto occupant = targetTile->takePiece();
                        if (occupant != nullptr) {
                            occupant->getOwner()->getStart()->putPiece(occupant);
                            occupant->retreat();
                        }
                    }
                    selectedTile->takePiece();
                    targetTile->putPiece(piece);
                    JukeBox::getInstance().playPiece();
                    piece->advance(rolledValue);
                    if (currentPlayer->getFinish()->getCount() == 7) { // wszystkie pionki na polu końcowym
                        //KONIEC GRY
                        std::cout << "koniec gry!" << std::endl;
                        std::cout << "wygrany:" << currentPlayer->getPlayername() << std::endl;
                        model->endgame(true);
                        GameState::getInstance().setFinished(true);
                        removePieceHighlight();
                        JukeBox::getInstance().playWin();
                        //resetGame();
                        return;
                    }
                    if (targetTile->getType() == flower) { //ponowny rzut
                        GameState::getInstance().setRolled(false);
                        removePieceHighlight();
                        model->updateTiles();
                    } else {
                        nextTurn();
                    }
                }
            }
        }

    }

    void nextTurn() {
        GameState::getInstance().setRolled(false);
        auto players = GameState::getInstance().getPlayers();
        removePieceHighlight();
        model->updateTiles();
        GameState::getInstance().swapPlayers();


        std::cout << "next turn" << std::endl;
    }

    void removePieceHighlight() {
        for (auto piece: GameState::getInstance().getPlayers().first->getPieces())
            piece->highlight(false);
    }

    void removeTileHighlight() {
        for (auto tile: GameState::getInstance().getBoard()->getTiles())
            tile->highlight(false);
    }

    void resetGame() {
        removePieceHighlight();
        GameState::getInstance().getDice()->clear();
        GameState::getInstance().getBoard()->clear();
        GameState::getInstance().getPlayers().first->putPiecesOnStart();
        GameState::getInstance().getPlayers().second->putPiecesOnStart();
        GameState::getInstance().setStarted(false);
        GameState::getInstance().setRolled(false);
        GameState::getInstance().setFinished(false);
        model->updateTiles();
        firstOrderRoll = -1;

    }

    virtual std::shared_ptr<MVC> handle(sf::Event event, sf::Vector2f mousePos) {
        removeTileHighlight();
        GameState::getInstance().getDice()->highlight(0);
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto target: clickables) {
                auto clickEvent = target->click(mousePos);
                if (clickEvent != nullptr) {
                    switch (clickEvent->getType()) {
                        case dice:

                            if (GameState::getInstance().getStarted()) {
                                if (rollDice()) {
                                    std::cout << "dice was rolled" << std::endl;
                                    if (!checkValidMoves()) {
                                        nextTurn();
                                    }
                                }
                            } else {
                                if (firstOrderRoll == -1) {
                                    rollDice();
                                    firstOrderRoll = GameState::getInstance().getDice()->getValue();
                                    GameState::getInstance().setRolled(false);
                                    std::cout << "rzut player1" << std::endl;
                                    GameState::getInstance().swapPlayers();
                                } else {
                                    rollDice();
                                    int secondOrderRoll = GameState::getInstance().getDice()->getValue();
                                    while (firstOrderRoll == secondOrderRoll) {
                                        GameState::getInstance().getDice()->roll();
                                        secondOrderRoll = GameState::getInstance().getDice()->getValue();
                                    }
                                    if (firstOrderRoll < secondOrderRoll) {
                                        std::cout << "player2 zaczyna" << std::endl;

                                    } else if (secondOrderRoll < firstOrderRoll) {
                                        std::cout << "player1 zaczyna" << std::endl;
                                        GameState::getInstance().swapPlayers();
                                    }

                                    GameState::getInstance().setRolled(false);
                                    GameState::getInstance().setStarted(true);
                                    firstOrderRoll = -1;
                                }
                            }
                            break;
                        case board:
                            if (!GameState::getInstance().getFinished())handleBoard(clickEvent);

                            break;
                        case help:
                            std::cout << "HELP" << std::endl;

                            return rulesMVC;
                            break;
                        case quit:
                            std::cout << "QUIT" << std::endl;
                            if (GameState::getInstance().getFinished()) resetGame(); // jeśli gra się skończyła to wyjście powinno ją zresetować
                            return quitMVC;
                            break;
                        case reset:
                            std::cout << "RESET" << std::endl;
                            resetGame();

                            break;
                    }
                }
            }

        } else {
            for (auto target: clickables) { //najechanie kursorem
                auto clickEvent = target->hover(mousePos);
                if (clickEvent and not GameState::getInstance().getFinished()) {
                    switch (clickEvent->getType()) {
                        case board:
                            if (GameState::getInstance().getRolled()) {
                                auto position = clickEvent->getPosition();
                                auto board = GameState::getInstance().getBoard();
                                auto hoveredTile = board->getTile(position);
                                auto hoveredPiece = hoveredTile->getPiece();
                                int rolledValue = GameState::getInstance().getDice()->getValue();
                                if (hoveredPiece and hoveredPiece->isHighlighted()) {

                                    auto targetTile = board->getTile(hoveredPiece->getTargetTileIndex(rolledValue));
                                    if (targetTile)targetTile->highlight(true);
                                }
                            }
                            break;
                        case dice:
                            if (GameState::getInstance().getRolled())
                                GameState::getInstance().getDice()->highlightForbidden();
                            else
                                GameState::getInstance().getDice()->highlight(1);
                            //
                    }
                }
            }

        }
        //else if (event.type == sf::Event::KeyPressed) {
        //	if (event.key.code == sf::Keyboard::Space) {
        //		model->rollDice();
        //	}
        //

        //}
        return selfMVC;
    }

    void setQuit(std::shared_ptr<MVC> mvc) {
        quitMVC = mvc;
    }

    void setRules(std::shared_ptr<MVC> mvc) {
        rulesMVC = mvc;
    }

    void setSelf(std::shared_ptr<MVC> mvc) {
        selfMVC = mvc;
    }

};