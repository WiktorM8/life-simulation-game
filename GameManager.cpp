//
// Created by Wiktor on 12.04.2025.
//

#include "GameManager.h"

#include <iostream>
#include <filesystem>

#include "World.h"

GameManager::GameManager() = default;

GameManager::~GameManager() {
    if (this->world != nullptr) {
        this->deleteWorld();
    }
}

void GameManager::displayMenu() const {
    std::cout << "Life simulation" << std::endl;
    std::cout << "n) nowa gra" << std::endl;
    std::cout << "l) wczytaj gre" << std::endl;
    std::cout << "esc) wyjdz z gry" << std::endl;
}


World* GameManager::createWorld() {
    system("cls");
    int width, height;
    std::cout << "Podaj szerokosc swiata: ";
    std::cin >> width;
    std::cout << "Podaj wysokosc swiata: ";
    std::cin >> height;
    std::cout << "Swiat stworzony z wymiarami x=" << width << " y=" << height << std::endl;
    std::cout << "Nacisnij dowolny przycisk aby zaczac gre..." << std::endl;

    const auto world = new World(width, height, this);
    this->world = world;
    world->generateStartingOrganisms();
    world->mergeNewOrganisms();
    world->draw();
    return world;
}

World* GameManager::loadWorld(const std::string& exe_path) {
    system("cls");
    std::string filename;
    const std::string directory = "./saves/";
    const std::filesystem::path exePath = std::filesystem::path(exe_path).parent_path();
    current_path(exePath);

    std::cout << "Podaj nazwe pliku do wczytania swiata: ";
    std::cin >> filename;
    filename = directory + filename + ".wdata";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Nie mozna otworzyc pliku do wczytania!" << std::endl;
        std::cout << "Nacisnij dowolny przycisk aby kontynuowac..." << std::endl;
        system("pause");
        return this->world;
    }
    if (this->world != nullptr) this->deleteWorld();
    this->world = new World(0, 0, this);
    this->world->loadFromFile(file);
    file.close();
    this->world->mergeNewOrganisms();
    std::cout << "Swiat zostal wczytany!" << std::endl;
    std::cout << "Nacisnij dowolny przycisk aby kontynuowac..." << std::endl;
    system("pause");
    this->world->draw();
    return this->world;
}

void GameManager::deleteWorld() {
    if (this->getWorld() == nullptr) {
        std::cout << "Nie ma swiata do usuniecia!" << std::endl;
        return;
    }
    this->getWorld()->clearWorld();
    this->playerAlive = false;
    delete this->world;
    this->world = nullptr;
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

void GameManager::setWorld(World* world) {
    this->world = world;
}

World* GameManager::getWorld() const {
    return this->world;
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

void GameManager::saveWorldToFile(const std::string& exe_path) const {
    system("cls");
    std::string filename;
    const std::string directory = "./saves/";
    const std::filesystem::path exePath = std::filesystem::path(exe_path).parent_path();
    current_path(exePath);
    std::filesystem::create_directories(directory);

    std ::cout << "Podaj nazwe pliku do zapisu swiata: ";
    std::cin >> filename;
    filename = directory + filename + ".wdata";
    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    std::cout << "Zapisuje swiat do pliku: " << filename << std::endl;
    if (!file.is_open()) {
        std::cout << "Nie mozna otworzyc pliku do zapisu!" << std::endl;
        std::cout << "Nacisnij dowolny przycisk aby kontynuowac..." << std::endl;
        system("pause");
        return;
    }

    this->getWorld()->saveToFile(file);
    std::cout << "Swiat zostal zapisany!" << std::endl;
    std::cout << "Nacisnij dowolny przycisk aby kontynuowac..." << std::endl;
    system("pause");
    file.close();
}

