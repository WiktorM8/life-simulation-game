//
// Created by Wiktor on 14.04.2025.
//

#include "Antelope.h"

#include <iostream>
#include <windows.h>
#include <random>
#include <algorithm>
#include <vector>

Antelope::Antelope(const Position position, World *world)
        : Animal(position, 4, 4, ANTELOPE, world) {}

Antelope::~Antelope() = default;

std::unique_ptr<Animal> Antelope::makeChild() const {
    const auto antelope = new Antelope(this->getPosition(), this->getWorld());
    return std::unique_ptr<Animal>(antelope);
}

void Antelope::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    std::cout << "A";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}

void Antelope::collision(Organism* other) {
    if (other->getType() == ANIMAL) {
        if (const auto other_animal = dynamic_cast<Animal*>(other)) {
            if (other_animal->getStrength() > this->getStrength()) {
                const int escape_chance = std::rand() % 2;
                if (escape_chance == 0) {
                    std::optional<Position> new_position = this->getRandomFreePosition();
                    if (new_position != std::nullopt) {
                        this->getWorld()->addMessage("Antylopa uciekla od walki z " + other_animal->getSpeciesName() +
                                                " z pola x=" +
                                                 std::to_string(this->getPositionX() + 1) + ", y=" +
                                                 std::to_string(this->getPositionY() + 1) + " na pole x=" +
                                                 std::to_string(new_position->x + 1) + ", y=" +
                                                 std::to_string(new_position->y + 1));
                        this->moveTo(new_position.value());
                        return;
                    }
                }
            }
        }
    }
    Animal::collision(other);
}

bool Antelope::defendAttack(Organism* attacker) {
    const auto animal_attacker = dynamic_cast<Animal*>(attacker);
    if (animal_attacker == nullptr) {
        this->getWorld()->addMessage("Not an animal");
        return false;
    }
    if (attacker->getStrength() > this->getStrength()) {
        const int escape_chance = std::rand() % 2;
        if (escape_chance == 0) {
            std::optional<Position> new_position = this->getRandomFreePosition();
            if (new_position != std::nullopt) {
                this->getWorld()->addMessage("Antylopa uciekla od walki z " + animal_attacker->getSpeciesName() +
                                        " z pola x=" +
                                         std::to_string(this->getPositionX() + 1) + ", y=" +
                                         std::to_string(this->getPositionY() + 1) + " na pole x=" +
                                         std::to_string(new_position->x + 1) + ", y=" +
                                         std::to_string(new_position->y + 1));
                this->moveTo(new_position.value());
                return true;
            }
        }
    }
    return false;
}

void Antelope::makeMove() {
    const int worldWidth = this->getWorld()->getWidth();
    const int worldHeight = this->getWorld()->getHeight();

    int newX = this->getPositionX();
    int newY = this->getPositionY();

    int moves = rand() % 2 + 1;

    while (moves-- > 0) {
        const int axis = std::rand() % 3; // 0 - double horizontal, 1 - double vertical, 2 - mixed
        if (axis == 0) {
            while (true) {
                newX += ((std::rand() % 3) - 1)*2;
                if (newX >= 0 && newX < worldWidth) {
                    break;
                }
            }
        } else if (axis == 1) {
            while (true) {
                newY += ((std::rand() % 3) - 1)*2;
                if (newY >= 0 && newY < worldHeight) {
                    break;
                }
            }
        } else {
            while (true) {
                newX += ((std::rand() % 3) - 1);
                newY += ((std::rand() % 3) - 1);
                if (newX >= 0 && newX < worldWidth && newY >= 0 && newY < worldHeight) {
                    break;
                }
            }
        }
    }

    // Move the animal to the new position
    this->moveTo(newX, newY);
}