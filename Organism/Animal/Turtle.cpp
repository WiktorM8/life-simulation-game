//
// Created by Wiktor on 14.04.2025.
//

#include "Turtle.h"

#include <iostream>
#include <windows.h>
#include <random>

Turtle::Turtle(const Position position, World *world)
        : Animal(position, 2, 1, TURTLE, world) {}

Turtle::~Turtle() = default;

std::unique_ptr<Animal> Turtle::makeChild() const {
    const auto turtle = new Turtle(this->getPosition(), this->getWorld());
    return std::unique_ptr<Animal>(turtle);
}

void Turtle::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "T";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}

void Turtle::attack(Animal* other) {
    if (other->getStrength() > this->getStrength() && other->getStrength() < 5) {
        other->moveTo(other->getLastPosition());
        return;
    }
    Animal::attack(other);
}

bool Turtle::defendAttack(Organism* attacker) {
    const auto animal_attacker = dynamic_cast<Animal*>(attacker);
    if (animal_attacker == nullptr) {
        this->getWorld()->addMessage("Not an animal");
        return false;
    }
    if (attacker->getStrength() < 5) {
        this->getWorld()->addMessage("Zwierze typu " + animal_attacker->getSpeciesName() + " nie moze zaatakowac zoltwia na pozycji x=" +
                                     std::to_string(this->getPositionX() + 1) + ", y=" +
                                     std::to_string(this->getPositionY() + 1));
        animal_attacker->moveTo(animal_attacker->getLastPosition());
        return true;
    }
    return false;
}

void Turtle::makeMove() {
    if (const int rand = std::rand() % 4; rand != 0) {
        return;
    }

    Animal::makeMove();
}