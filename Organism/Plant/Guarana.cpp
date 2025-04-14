//
// Created by Wiktor on 14.04.2025.
//

#include "Guarana.h"
#include "../Animal/Animal.h"
#include <iostream>
#include <windows.h>


Guarana::Guarana(const Position position, World *world) : Plant(position, 0, 0, GUARANA, world) {}

Guarana::~Guarana() = default;

std::unique_ptr<Plant> Guarana::makeChild() const {
    const auto guarana = new Guarana(this->getPosition(), this->getWorld());
    return std::unique_ptr<Plant>(guarana);
}

void Guarana::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (4 << 4));
    std::cout << "G";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Guarana::collision(Organism* other) {
    if (other->getType() == ANIMAL) {
        auto animal = dynamic_cast<Animal*>(other);
        if (animal != nullptr) {
            animal->setStrength(animal->getStrength() + 3);
            this->setAlive(false);
            this->getWorld()->addMessage("Guarana zostala zjedzona przez zwierze typu " + animal->getSpeciesName() +
                                         " na pozycji x=" + std::to_string(this->getPositionX() + 1) +
                                         ", y=" + std::to_string(this->getPositionY() + 1));
        }
    }
}