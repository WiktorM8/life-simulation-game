//
// Created by Wiktor on 12.04.2025.
//

#include "GameManager.h"

#include <iostream>

#include "World.h"

GameManager::GameManager() = default;

World* GameManager::createWorld() {
    int width, height;
    std::cout << "Enter world width: ";
    std::cin >> width;
    std::cout << "Enter world height: ";
    std::cin >> height;
    std::cout << "World created with dimensions: " << width << "x" << height << std::endl;
    std::cout << "Press any key to start the game..." << std::endl;

    return new World(width, height);
}
