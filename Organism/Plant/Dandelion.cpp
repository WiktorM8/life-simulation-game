//
// Created by Wiktor on 14.04.2025.
//

#include "Dandelion.h"

#include <iostream>
#include <windows.h>

Dandelion::Dandelion(const Position position, World *world) : Plant(position, 0, 0, DANDELION, world) {}

Dandelion::~Dandelion() = default;

std::unique_ptr<Plant> Dandelion::makeChild() const {
    const auto dandelion = new Dandelion(this->getPosition(), this->getWorld());
    return std::unique_ptr<Plant>(dandelion);
}

void Dandelion::action() {
    if (!this->isAlive()) return;

    this->spread();
    this->spread();
    this->spread();
}

void Dandelion::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
    std::cout << "D";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}