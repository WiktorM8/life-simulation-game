//
// Created by Wiktor on 13.04.2025.
//

#include "Fox.h"

#include <iostream>
#include <windows.h>

Fox::Fox(const Position position, World *world)
        : Animal(position, 3, 7, FOX, world) {}

Fox::~Fox() = default;

std::unique_ptr<Animal> Fox::makeChild() const {
    const auto fox = new Fox(this->getPosition(), this->getWorld());
    return std::unique_ptr<Animal>(fox);
}

void Fox::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout << "F";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}

bool Fox::isFieldSafe(const int x, const int y) const {
    // Check if the field is not occupied by a stronger animal
    for (const auto& organism : this->getWorld()->getOrganisms()) {
        if (organism->getPositionX() == x && organism->getPositionY() == y &&
            organism->getStrength() > this->getStrength()) {
            return false;
        }
    }

    return true;
}

void Fox::makeMove() {
    const int worldWidth = this->getWorld()->getWidth();
    const int worldHeight = this->getWorld()->getHeight();

    const int directions[4][2] = {
        {0, -1},  // up
        {0, 1},   // down
        {-1, 0},  // left
        {1, 0}    // right
    };

    std::vector<std::pair<int, int>> safePositions;

    for (const auto& dir : directions) {
        int newX = this->getPositionX() + dir[0];
        int newY = this->getPositionY() + dir[1];

        if (newX >= 0 && newX < this->getWorld()->getWidth() &&
            newY >= 0 && newY < this->getWorld()->getHeight() &&
            this->isFieldSafe(newX, newY)) {
                safePositions.emplace_back(newX, newY);
            }
    }
    if (safePositions.empty()) {
        return;
    }
    const int randomIndex = std::rand() % safePositions.size();
    std::pair<int, int> chosen_position = safePositions[randomIndex];

    // Move the animal to the new position
    this->moveTo(chosen_position.first, chosen_position.second);
}

