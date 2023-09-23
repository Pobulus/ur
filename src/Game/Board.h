/** @file */
#pragma once

#include <vector>
#include "Tile.h"
#include "../UI/Clickable.h"

class Board : public Clickable {
    int getIndexFromCoords(int x, int y) {
        if (x < 0 or x >= tilesCols or y < 0 or y >= tilesRows)
            return -1;
        return x + y * tilesCols;
    }


    const float tileEdge = 175.f;
    const float top = 200.f;
    const float left = 125.f;
    std::vector<std::shared_ptr<Tile>> tiles;

    static const int tilesRows = 3;
    static const int tilesCols = 8;

    int tileTypes[tilesRows * tilesCols] = {
            2, 1, 1, 1, 0, 0, 2, 1,
            1, 1, 1, 2, 1, 1, 1, 1,
            2, 1, 1, 1, 0, 0, 2, 1
    };
public:
    Board() {
        for (int i = 0; i < 24; i++) {
            auto tile = std::make_shared<Tile>(
                    sf::Vector2f(left + i % tilesCols * tileEdge, top + i / tilesCols * tileEdge),
                    static_cast<tileType>(tileTypes[i]));
            tiles.push_back(tile);
        }
        area = {left, top, tilesCols * tileEdge, tilesRows * tileEdge};
    }

    void clear() {
        for (auto tile: tiles) {
            tile->clearPieces();
        }
    }

    std::shared_ptr<Tile> getTile(sf::Vector2i coords) {
        return getTile(coords.x, coords.y);
    }

    std::shared_ptr<Tile> getTile(int x, int y) {
        return getTile(getIndexFromCoords(x, y));
    }

    std::shared_ptr<Tile> getTile(int index) {
        if (index < 0 or index >= tiles.size())
            return nullptr;
        return tiles[index];
    }

    std::vector<std::shared_ptr<Tile>> getTiles() {
        return tiles;
    }

    std::shared_ptr<ClickEvent> click(sf::Vector2f position) {
        if (area.contains(position)) {
            int tileX = (position.x - area.left) / 175;
            int tileY = (position.y - area.top) / 175;
            std::cout << "board:" << tileX << ", " << tileY << std::endl;
            return std::make_shared<BoardClicked>(sf::Vector2i(tileX, tileY));
        }
        return nullptr;
    };

    std::shared_ptr<ClickEvent> hover(sf::Vector2f position) {
        if (area.contains(position)) {
            int tileX = (position.x - area.left) / 175;
            int tileY = (position.y - area.top) / 175;
            return std::make_shared<BoardClicked>(sf::Vector2i(tileX, tileY));
        }
        return nullptr;
    }

};