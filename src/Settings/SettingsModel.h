/** @file */
#pragma once

#include "../MVC/Model.h"
#include "../UI/TextButton.h"
#include <iostream>
#include <regex>
#include <filesystem>
#include "Setting.h"

class SettingsModel : public Model {
    std::vector<std::string> languages;
    const std::vector<std::string> colorSchemes{"Settings/colors.js", "Settings/dark.js"};
    const std::vector<std::string> soundOn{"no", "yes"};
    Setting languageSetting;
    Setting colorSetting;
    Setting soundSetting;

    std::shared_ptr<Button> quitButton;
    sf::Text title;
    sf::Font font;
    std::shared_ptr<TextButton> languageButton, colorButton, soundButton;
    const float textSize = 50.f;

    void setTitle() {
        font = Config::getInstance().getFont();
        title.setString(Config::getInstance().getTranslation("settings"));
        title.setFillColor(Config::getInstance().getColor("tile"));

        auto textGlobalBounds = title.getGlobalBounds();
        auto center = sf::Vector2f(title.getGlobalBounds().width, title.getGlobalBounds().height) / 2.f;
        auto localBounds = center + sf::Vector2f(title.getLocalBounds().left, title.getLocalBounds().top);
        auto rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
        title.setOrigin(rounded);
        title.setPosition({830.f, 200.f});
    }

    void loadPreferences() {
        std::ifstream saveFile("Settings/preferences.js");
        if (saveFile) {
            json saveJSON = json::parse(saveFile);
            colorSetting.setCurrent(saveJSON["color"]);
            languageSetting.setCurrent(saveJSON["language"]);
            soundSetting.setCurrent(saveJSON["sound"]);
            std::cout << saveJSON << "loaded" << std::endl;
        }
        Config::getInstance().loadTranslationConfig(languageSetting.getName());
        Config::getInstance().loadColorConfig(colorSetting.getName());
        JukeBox::getInstance().setSound(soundSetting.getCurrent());
    }

public:
    SettingsModel() {
        const std::regex languageFile("[A-Z]{2}\\.js");
        for (const auto &file: std::filesystem::recursive_directory_iterator("Settings/")) {
            if (std::regex_match(file.path().filename().u8string(), languageFile)) {
                languages.push_back(file.path().u8string());
                std::cout << file.path().u8string() << std::endl;
            }
        }

        languageSetting.setOptions(languages);
        colorSetting.setOptions(colorSchemes);
        soundSetting.setOptions(soundOn);
        font.loadFromFile("Resources/Roboto-Regular.ttf");
        title.setFont(font);
        title.setCharacterSize(180.f);
        title.setPosition({200.f, 0.f});

        quitButton = std::make_shared<Button>("Resources/quit.png", sf::Vector2f(8.5 * 175.f, 50.f), quit);

        languageButton = std::make_shared<TextButton>("", sf::Vector2f(1300.f, 150.f), "Resources/settingbg.png",
                                                      sf::Vector2f(180.f, 400.f), language);
        colorButton = std::make_shared<TextButton>("", sf::Vector2f(1300.f, 150.f), "Resources/settingbg.png",
                                                   sf::Vector2f(180.f, 600.f), color);
        soundButton = std::make_shared<TextButton>("", sf::Vector2f(1300.f, 150.f), "Resources/settingbg.png",
                                                   sf::Vector2f(180.f, 800.f), sound);

        loadPreferences();
    }

    virtual ~SettingsModel() {


    };

    void toggleColor() {
        colorSetting.toggle();
        Config::getInstance().loadColorConfig(colorSetting.getName());
    }

    void toggleLanguage() {
        languageSetting.toggle();
        Config::getInstance().loadTranslationConfig(languageSetting.getName());

    }

    void toggleSound() {
        soundSetting.toggle();
        JukeBox::getInstance().setSound(soundSetting.getCurrent());
    }

    virtual std::vector<std::shared_ptr<Clickable>> getClickables() {
        std::vector<std::shared_ptr<Clickable>> out;
        out.push_back(quitButton);
        out.push_back(languageButton);
        out.push_back(colorButton);
        out.push_back(soundButton);


        return out;
    }

    virtual std::vector<sf::Drawable *> getContent() {
        std::vector<sf::Drawable *> out;
        languageButton->setText(Config::getInstance().getTranslation("language"), textSize);
        colorButton->setText(Config::getInstance().getTranslation("color"), textSize);
        soundButton->setText(Config::getInstance().getTranslation("sound") +
                             Config::getInstance().getTranslation(soundSetting.getName()), textSize);
        out.push_back(quitButton->getDrawable());
        out.push_back(languageButton->getDrawable());
        out.push_back(colorButton->getDrawable());
        out.push_back(soundButton->getDrawable());

        setTitle();
        out.push_back(&title);


        return out;
    }

    void savePreferences() {
        json saveJSON;
        saveJSON["color"] = colorSetting.getCurrent();
        saveJSON["language"] = languageSetting.getCurrent();
        saveJSON["sound"] = soundSetting.getCurrent();
        std::ofstream saveFile("Settings/preferences.js");
        saveFile << saveJSON;
        std::cout << saveJSON << "saved" << std::endl;
        saveFile.close();
    }


};
