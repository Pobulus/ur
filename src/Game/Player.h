/** @file */
#pragma once

#include "Tile.h"

class Player {

    int score;
    std::shared_ptr<Tile> start, finish;
    std::vector<std::shared_ptr<Piece>> pieces;
    sf::Texture pieceTexture;
    std::string playername;
public:
    Player(std::shared_ptr<Tile> start, std::shared_ptr<Tile> finish, std::vector<int> path, std::string playername)
            : start(start), finish(finish), playername(playername) {
        pieceTexture.loadFromFile("Resources/piece.png");
        for (int i = 0; i < 7; i++) {
            auto piece = std::make_shared<Piece>(playername, this, path);
            piece->setTexture(pieceTexture);

            pieces.push_back(piece);
        }
        putPiecesOnStart();
    }

    void putPiecesOnStart() {
        for (auto piece: pieces) {
            start->putPiece(piece);
            piece->retreat();
        }
    }

    int getScore() const {
        return score;
    }

    std::shared_ptr<Tile> &getStart() {
        return start;
    }

    std::shared_ptr<Tile> &getFinish() {
        return finish;
    }

    std::vector<std::shared_ptr<Piece>> getPieces() {
        return pieces;
    }

    std::string getPlayername() {
        return playername;
    }

};