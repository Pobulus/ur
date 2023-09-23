/** @file */
#pragma once

#include "Tile.h"
#include "Piece.h"
#include "Dice.h"
#include "Player.h"
#include "../UI/Button.h"
#include "Board.h"

#include <vector>
#include <memory>
#include <fstream>

//JSON
#include "../Lib/json.hpp"

// for convenience
using json = nlohmann::json;

class GameState {
    std::pair<std::shared_ptr<Player>, std::shared_ptr<Player>> players;
    std::shared_ptr<Dice> dice;
    std::shared_ptr<Board> board;
    bool rolled = false;
    bool started = false;
    bool finished = false;

    GameState() {

        board = std::make_shared<Board>();

        std::vector<int> path1 = {20, 19, 18, 17, 16, 8, 9, 10, 11, 12, 13, 14, 15, 23, 22, 21};
        std::vector<int> path2 = {4, 3, 2, 1, 0, 8, 9, 10, 11, 12, 13, 14, 15, 7, 6, 5};

        players.first = std::make_shared<Player>(board->getTile(4, 2), board->getTile(5, 2), path1, "player1");
        players.second = std::make_shared<Player>(board->getTile(4, 0), board->getTile(5, 0), path2, "player2");
        dice = std::make_shared<Dice>();
        loadGameState();
    }

public:
    ~GameState() {
        saveGameState();
    }

    void operator=(const GameState) = delete;

    static GameState &getInstance() {
        static GameState singleton;
        return singleton;
    }

    bool getRolled() {
        return rolled;
    }

    void setRolled(bool state) {
        rolled = state;
    }

    bool getStarted() {
        return started;
    }

    void setStarted(bool state) {
        started = state;
    }

    bool getFinished() {
        return finished;
    }

    void setFinished(bool state) {
        finished = state;
    }

    std::pair<std::shared_ptr<Player>, std::shared_ptr<Player>> getPlayers() {
        return players;
    }

    void swapPlayers() {
        /*std::shared_ptr<Player> temp = players.first;
        players.first = players.second;
        players.second = temp;*/
        std::swap(players.first, players.second);
    }

    std::shared_ptr<Dice> getDice() {
        return dice;
    }

    std::shared_ptr<Board> getBoard() {
        return board;
    }

    void loadPlayerState(std::shared_ptr<Player> player, json &config) {

        for (auto index: config[player->getPlayername() + "-pieces"]) {
            auto tempPiece = player->getStart()->takePiece();
            tempPiece->setProgress(index);
            auto targetTile = board->getTile(tempPiece->getTargetTileIndex(0));
            targetTile->putPiece(tempPiece);
            int progress = index;
            std::cout << progress << " ";

        }
        std::cout << std::endl;

    }

    void savePlayerState(std::shared_ptr<Player> player, json &config) {
        for (auto piece: player->getPieces()) {
            config[player->getPlayername() + "-pieces"] += piece->getProgress();
        }
    }


    void loadGameState() {
        auto saveFile = std::fstream("Settings/gameState.js");

        if (saveFile) {
            auto saveJSON = json::parse(saveFile);
            if (saveJSON["currentPlayer"] != players.first->getPlayername())
                swapPlayers();
            rolled = saveJSON["rolled"];
            started = saveJSON["started"];
            dice->setState(saveJSON["diceState"]);
            loadPlayerState(players.first, saveJSON);
            loadPlayerState(players.second, saveJSON);
        }
    }

    void saveGameState() {
        std::ofstream saveFile("Settings/gameState.js");
        if (!finished) {
            json saveJSON;
            saveJSON["diceState"] = dice->getState();
            saveJSON["rolled"] = rolled;
            saveJSON["started"] = started;
            saveJSON["currentPlayer"] = players.first->getPlayername();
            savePlayerState(players.first, saveJSON);
            savePlayerState(players.second, saveJSON);


            saveFile << saveJSON;

        } else { // jeśli gra skończona, zapisz stan poczatkowy
            saveFile
                    << "{\"currentPlayer\":\"player1\", \"diceState\" : 0, \"player1-pieces\" : [0, 0, 0, 0, 0, 0, 0] , \"player2-pieces\" : [0, 0, 0, 0, 0, 0, 0] , \"rolled\" : false, \"started\" : false}";
        }
        saveFile.close();

    }

};