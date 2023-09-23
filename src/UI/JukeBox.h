/** @file */
#pragma once

#include <SFML/Audio.hpp>

class JukeBox {
    sf::SoundBuffer piece, button, dice, win;
    sf::Sound sound;
    bool mute = false;

    JukeBox() {
        piece.loadFromFile("Resources/piece.ogg");
        button.loadFromFile("Resources/button.ogg");
        dice.loadFromFile("Resources/dice.ogg");
        win.loadFromFile("Resources/win.ogg");
    }

    void play() {
        if (!mute)
            sound.play();
    }

public:
    static JukeBox &getInstance();

    void playPiece() {
        sound.setBuffer(piece);
        play();
    }

    void playDice() {
        sound.setBuffer(dice);
        play();
    }

    void playButton() {
        sound.setBuffer(button);
        play();
    }

    void playWin() {
        sound.setBuffer(win);
        play();
    }

    void setSound(bool value) {
        mute = !value;
    }
};

JukeBox &JukeBox::getInstance() {
    static JukeBox singleton;
    return singleton;
}