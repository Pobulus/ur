/** @file */
#pragma once
//JSON
#include "../Lib/json.hpp"

// for convenience
using json = nlohmann::json;

#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <iostream>
#include <filesystem>


class Config {
    std::map<std::string, sf::Color> colors;
    std::map<std::string, sf::String> translations;
    sf::Font globalFont;

    Config() {
        loadColorConfig("Settings/colors.js");

        loadTranslationConfig("Settings/EN.js");

    }

    void loadColor(std::string colorName, json JSON) {
        auto color = JSON[colorName];

        colors[colorName] = sf::Color(color[0], color[1], color[2]);
    }

    void loadTranslation(std::string translationName, json JSON) {
        std::string translation = JSON[translationName];
        translations[translationName] = sf::String::fromUtf8(translation.begin(), translation.end());
    }

public:
    void loadFont(std::string fontName) {
        globalFont.loadFromFile(fontName);
    }

    static Config &getInstance();

    sf::Color getColor(std::string name) {
        return colors[name];
    }

    sf::String getTranslation(std::string name) {
        return translations[name];
    }

    void loadTranslationConfig(std::string configName) {
        std::ifstream configFile(configName);
        json configJSON = json::parse(configFile);
        loadFont(configJSON["font"]);
        loadTranslation("settings", configJSON);
        loadTranslation("play", configJSON);
        loadTranslation("sound", configJSON);
        loadTranslation("color", configJSON);
        loadTranslation("language", configJSON);
        loadTranslation("quitPrompt", configJSON);
        loadTranslation("yes", configJSON);
        loadTranslation("no", configJSON);

    }

    sf::Font getFont() {
        return globalFont;
    }

    void loadColorConfig(std::string configName) {

        std::ifstream configFile(configName);
        json configJSON = json::parse(configFile);
        std::cout << configJSON.dump() << std::endl;


        loadColor("background", configJSON);
        loadColor("tile", configJSON);
        loadColor("text", configJSON);
        loadColor("player1", configJSON);
        loadColor("player2", configJSON);
        loadColor("selected", configJSON);
        loadColor("forbidden", configJSON);

    }

};

Config &Config::getInstance() {
    static Config singleton;
    return singleton;

}