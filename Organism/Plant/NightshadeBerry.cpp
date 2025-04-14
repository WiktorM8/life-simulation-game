//
// Created by Wiktor on 14.04.2025.
//

#include "NightshadeBerry.h"
#include "../Animal/Animal.h"

#include <iostream>
#include <windows.h>

NightshadeBerry::NightshadeBerry(const Position position, World *world) : Plant(position, 99, 0, NIGHTSHADE_BERRY, world) {}

NightshadeBerry::~NightshadeBerry() = default;

std::unique_ptr<Plant> NightshadeBerry::makeChild() const {
    const auto nightshadeBerry = new NightshadeBerry(this->getPosition(), this->getWorld());
    return std::unique_ptr<Plant>(nightshadeBerry);
}

void NightshadeBerry::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (1 << 4));
    std::cout << "N";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void NightshadeBerry::collision(Organism* other) {
    if (other->getType() == ANIMAL) {
        const auto animal = dynamic_cast<Animal*>(other);
        if (animal != nullptr) {
            animal->setAlive(false);
            this->setAlive(false);
            this->getWorld()->addMessage("Zwierze typu " + animal->getSpeciesName() +
                                         " zjadlo wilcza jagode, umiera na pozycji x=" + std::to_string(this->getPositionX() + 1) +
                                         ", y=" + std::to_string(this->getPositionY() + 1));
        }
    }
}
