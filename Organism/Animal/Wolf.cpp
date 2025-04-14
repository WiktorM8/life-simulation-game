//
// Created by Wiktor on 12.04.2025.
//

#include "Wolf.h"

#include <iostream>
#include <windows.h>

Wolf::Wolf(const Position position, World *world)
        : Animal(position, 9, 5, WOLF, world) {}

Wolf::~Wolf() = default;

std::unique_ptr<Animal> Wolf::makeChild() const {
    const auto wolf = new Wolf(this->getPosition(), this->getWorld());
    return std::unique_ptr<Animal>(wolf);
}

void Wolf::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::cout << "W";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}


