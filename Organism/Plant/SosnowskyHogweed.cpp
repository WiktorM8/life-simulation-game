//
// Created by Wiktor on 14.04.2025.
//

#include "SosnowskyHogweed.h"

#include "../Animal/Animal.h"
#include <iostream>
#include <windows.h>

SosnowskyHogweed::SosnowskyHogweed(const Position position, World *world)
        : Plant(position, 10, 0, SOSNOWSKY_HOGWEED, world) {
}

SosnowskyHogweed::~SosnowskyHogweed() = default;

std::unique_ptr<Plant> SosnowskyHogweed::makeChild() const {
    return std::make_unique<SosnowskyHogweed>(this->getPosition(), this->getWorld());
}

void SosnowskyHogweed::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 | (4 << 4));
    std::cout << "S";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void SosnowskyHogweed::collision(Organism* other) {
    if (other->getType() == ANIMAL) {
        const auto animal = dynamic_cast<Animal*>(other);
        if (animal != nullptr) {
            animal->setAlive(false);
            this->setAlive(false);
            /*this->getWorld()->addMessage("Zwierze typu " + animal->getSpeciesName() +
                                         " zjadlo barszcz Sosnowskiego, umiera na pozycji x=" + std::to_string(this->getPositionX() + 1) +
                                         ", y=" + std::to_string(this->getPositionY() + 1));*/
        }
    }
}

void SosnowskyHogweed::killNearbyAnimals() const {
    for (auto& organism : this->getWorld()->getOrganisms()) {
        if (organism->getType() == ANIMAL) {
            const auto animal = dynamic_cast<Animal*>(organism.get());
            if (animal != nullptr && animal->isAlive()) {
                if (animal->getPosition().x >= this->getPositionX() - 1 &&
                    animal->getPosition().x <= this->getPositionX() + 1 &&
                    animal->getPosition().y >= this->getPositionY() - 1 &&
                    animal->getPosition().y <= this->getPositionY() + 1 ) {
                        animal->setAlive(false);
                }
            }
        }
    }
}

void SosnowskyHogweed::action() {
    if (!this->isAlive()) return;

    this->killNearbyAnimals();
    this->spread();
}




