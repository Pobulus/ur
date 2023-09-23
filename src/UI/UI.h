/** @file */
#pragma once

#include "../Game/GameView.h"
#include "../Game/GameController.h"

#include "../Rules/RulesView.h"
#include "../Rules/RulesController.h"

#include "../Menu/MenuView.h"
#include "../Menu/MenuController.h"

#include "../Exit/ExitView.h"
#include "../Exit/ExitController.h"

#include "../Settings/SettingsView.h"
#include "../Settings/SettingsController.h"


#include <memory>
#include <SFML/Graphics.hpp>
#include "../MVC/MVC.h"

class UI {
    sf::RenderWindow window;
    std::shared_ptr<MVC> mvc, rulesMVC, gameMVC, menuMVC, exitMVC, settingsMVC;
    sf::Image icon;


    sf::View view;
    sf::Vector2f viewSize = {1660.f, 1000.f};

    void initializeMVCs() {
        gameMVC = std::make_shared<MVC>();
        rulesMVC = std::make_shared<MVC>();
        menuMVC = std::make_shared<MVC>();
        exitMVC = std::make_shared<MVC>();
        settingsMVC = std::make_shared<MVC>();
    }

    void initializeGame() {
        std::shared_ptr<GameModel> gameModel = std::make_shared<GameModel>();
        std::shared_ptr<GameView> gameView = std::make_shared<GameView>(gameModel);
        std::shared_ptr<GameController> gameController = std::make_shared<GameController>(gameModel);
        gameMVC->controller = gameController;
        gameMVC->model = gameModel;
        gameMVC->view = gameView;
        gameController->setSelf(gameMVC);
        gameController->setRules(rulesMVC);
        gameController->setQuit(menuMVC);
    }

    void initializeRules() {
        std::shared_ptr<RulesModel> rulesModel = std::make_shared<RulesModel>();
        std::shared_ptr<RulesView> rulesView = std::make_shared<RulesView>(rulesModel);
        std::shared_ptr<RulesController> rulesController = std::make_shared<RulesController>(rulesModel);
        rulesMVC->controller = rulesController;
        rulesMVC->model = rulesModel;
        rulesMVC->view = rulesView;
        rulesController->setSelf(rulesMVC);
        rulesController->setQuit(gameMVC);
    }

    void initializeMenu() {
        std::shared_ptr<MenuModel> menuModel = std::make_shared<MenuModel>();
        std::shared_ptr<MenuView> menuView = std::make_shared<MenuView>(menuModel);
        std::shared_ptr<MenuController> menuController = std::make_shared<MenuController>(menuModel);
        menuMVC->controller = menuController;
        menuMVC->model = menuModel;
        menuMVC->view = menuView;
        menuController->setSelf(menuMVC);
        menuController->setSettings(settingsMVC);
        menuController->setGame(gameMVC);
        menuController->setQuit(exitMVC);
    }

    void initializeExit() {
        std::shared_ptr<ExitModel> exitModel = std::make_shared<ExitModel>();
        std::shared_ptr<ExitView> exitView = std::make_shared<ExitView>(exitModel);
        std::shared_ptr<ExitController> exitController = std::make_shared<ExitController>(exitModel);
        exitMVC->controller = exitController;
        exitMVC->model = exitModel;
        exitMVC->view = exitView;
        exitController->setSelf(exitMVC);
        exitController->setMenu(menuMVC);

    }

    void initializeSettings() {
        std::shared_ptr<SettingsModel> settingsModel = std::make_shared<SettingsModel>();
        std::shared_ptr<SettingsView> settingsView = std::make_shared<SettingsView>(settingsModel);
        std::shared_ptr<SettingsController> settingsController = std::make_shared<SettingsController>(settingsModel);
        settingsMVC->controller = settingsController;
        settingsMVC->model = settingsModel;
        settingsMVC->view = settingsView;
        settingsController->setSelf(settingsMVC);
        settingsController->setQuit(menuMVC);


    }

public:
    UI() {
        window.create(sf::VideoMode(viewSize.x, viewSize.y), "The Royal Game of Ur", sf::Style::Resize);
        icon.loadFromFile("Resources/icon.png");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        initializeMVCs();
        initializeGame();
        initializeRules();
        initializeMenu();
        initializeExit();
        initializeSettings();
        mvc = menuMVC;
    }


    void engage() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::Resized) {
                    view.setSize(event.size.width, event.size.height);

                    float scale = std::max(viewSize.x / event.size.width, viewSize.y / event.size.height);
                    view.zoom(scale); //przeskaluj do szerokości
                    view.setCenter(viewSize.x / 2, viewSize.y / 2);

                    window.setView(view);
                } else {
                    if (mvc)
                        mvc = mvc->controller->handle(event, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                    else {
                        window.close();
                        break;
                    }

                }
            }

            window.clear();
            if (mvc != nullptr)
                mvc->view->show(window);
            else
                window.close();

            window.display();
        }
        settingsMVC = nullptr;
    }

};