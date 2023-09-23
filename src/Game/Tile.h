/** @file */
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Settings/Config.h"
#include "../UI/Drawable.h"
#include "Piece.h"

enum tileType {
    empty = 0,
    normal,
    flower
};

class Tile : public Highlightable, public Drawable {
    tileType type;

    sf::Text number;
    sf::Font numberFont;

    sf::Sprite body, tile;
    sf::Texture tileTexture;
    sf::RenderTexture texture;
    std::vector<std::shared_ptr<Piece>> piecesOnTile;

    //Wyśrodkowuje tekst na kafelku
    void centerNumber() {
        auto bodyBounds = body.getGlobalBounds();
        auto numberBounds = number.getGlobalBounds();
        auto center = sf::Vector2f(numberBounds.width, numberBounds.height) / 2.f;
        auto localBounds = center + sf::Vector2f(number.getLocalBounds().left, number.getLocalBounds().top);
        auto rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
        number.setOrigin(rounded);
        number.setPosition({80.f, 80.f});

    }

public:
    Tile(sf::Vector2f position, tileType type) : type(type) {
        std::string texturename;
        switch (type) {
            case empty:
                texturename = "Resources/empty.png";
                break;
            case normal:
                texturename = "Resources/tile.png";
                break;
            case flower:
                texturename = "Resources/flower.png";
                break;
            default:
                break;
        }
        //Inicjalizjacja tekstu wyświetlającego liczbę pionków
        numberFont.loadFromFile("Resources/alhambra.ttf");
        //numberFont.loadFromFile("Resources/Roboto-Regular.ttf");
        number.setFont(numberFont);
        number.setCharacterSize(70.f);
        number.setFillColor(Config::getInstance().getColor("tile"));

        //tile to tło
        tileTexture.loadFromFile(texturename);
        tile.setTexture(tileTexture);
        tile.setScale({0.2, 0.2});


        texture.create(160.f, 160.f);
        body.setTexture(texture.getTexture());
        body.setPosition(position);
        display();

    }

    void setColor(sf::Color color) {
        body.setColor(color);
    }

    sf::Drawable *getDrawable() {
        return &body;
    }

    // aktualizuje zawartość tekstury body
    void display() {
        texture.clear(sf::Color::Transparent);
        //tile.setColor(Config::getInstance().getColor("tile"));
        number.setFillColor(Config::getInstance().getColor("tile"));
        texture.draw(tile);
        int pieceCount = piecesOnTile.size();
        if (pieceCount > 0) {
            //jeśli przynajmniej jeden pionek, wydrukuj ten na samej górze
            texture.draw(*(piecesOnTile.back()->getDrawable()));

            if (pieceCount > 1) { //jeśli więcej niż jeden, wyrysuj napis, który powie ile
                number.setString(std::to_string(pieceCount));
                centerNumber();
                texture.draw(number);
            }
        }
        texture.display();
    }

    sf::Vector2f getCoords() {
        return body.getPosition();
    }

    void putPiece(std::shared_ptr<Piece> p) {
        piecesOnTile.push_back(p);
        //p->setPosition(body.getPosition());
        display();
    }

    std::shared_ptr<Piece> getPiece() {
        if (!piecesOnTile.size())
            return nullptr;
        return piecesOnTile.back();
    }

    tileType getType() {
        return type;
    }

    std::shared_ptr<Piece> takePiece() {
        if (!piecesOnTile.size())
            return nullptr;
        std::shared_ptr<Piece> temp = piecesOnTile.back();
        piecesOnTile.pop_back();
        display();
        return temp;
    }

    int getCount() const {
        return piecesOnTile.size();
    }

    void clearPieces() {
        piecesOnTile.clear();
    }

    virtual void highlight(bool state) {
        highlighted = state;

        if (highlighted) {
            tile.setColor(Config::getInstance().getColor("selected"));
        } else {
            tile.setColor(Config::getInstance().getColor("tile"));
        }
        display();

    }
};
