//
// Created by Wiktor on 14.04.2025.
//

#include "Grass.h"

#include <iostream>
#include <windows.h>

Grass::Grass(const Position position, World *world) : Plant(position, 0, 0, GRASS, world) {}

Grass::~Grass() = default;

std::unique_ptr<Plant> Grass::makeChild() const {
    const auto grass = new Grass(this->getPosition(), this->getWorld());
    return std::unique_ptr<Plant>(grass);
}

void Grass::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (2 << 4));
    std::cout << "G";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

