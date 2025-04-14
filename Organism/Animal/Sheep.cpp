//
// Created by Wiktor on 13.04.2025.
//

#include "Sheep.h"

#include <iostream>
#include <windows.h>

Sheep::Sheep(const Position position, World *world)
        : Animal(position, 4, 4, SHEEP, world) {}

Sheep::~Sheep() = default;

std::unique_ptr<Animal> Sheep::makeChild() const {
    const auto sheep = new Sheep(this->getPosition(), this->getWorld());
    return std::unique_ptr<Animal>(sheep);
}

void Sheep::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    std::cout << "S";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}