//
// Created by Wiktor on 12.04.2025.
//

#include "GameManager.h"

#include <iostream>

#include "World.h"

GameManager::GameManager() = default;

World* GameManager::createWorld() {
    int width, height;
    std::cout << "Podaj szerokosc swiata: ";
    std::cin >> width;
    std::cout << "Podaj wysokosc swiata: ";
    std::cin >> height;
    std::cout << "Swiat stworzony z wymiarami x=" << width << " y=" << height << std::endl;
    std::cout << "Nacisnij dowolny przycisk aby zaczac gre..." << std::endl;

    return new World(width, height, this);
}

void GameManager::setPlayerDirection(const PlayerDirection direction) {
    this->playerDirection = direction;
}
PlayerDirection GameManager::getPlayerDirection() const {
    return playerDirection;
}

void GameManager::setPlayerAlive(const bool alive) {
    this->playerAlive = alive;
}

bool GameManager::isPlayerAlive() const {
    return playerAlive;
}

void GameManager::printPlayerDirection() const {
    if (!this->playerAlive) {
        std::cout << "Gracz nie zyje" << std::endl;
        return;
    }

    std::string text = "Gracz pojdzie w: ";
    switch (playerDirection) {
        case UP:
            text += "gore";
        break;
        case DOWN:
            text += "dol";
        break;
        case LEFT:
            text += "lewo";
        break;
        case RIGHT:
            text += "prawo";
        break;
        default:
            text += "Nieznany kierunek";
        break;
    }
    std::cout << text << std::endl;
}
