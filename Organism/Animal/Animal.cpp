//
// Created by Wiktor on 12.04.2025.
//

#include "Animal.h"

#include <iostream>

Animal::Animal(const int x, const int y, const int strength, const int initiative,
               const AnimalSpecies species, World* world)
        : Organism(x, y, strength, initiative, ANIMAL, world), species(species) {}

Animal::~Animal() = default;

void Animal::setSpecies(const AnimalSpecies species) {
    this->species = species;
}
AnimalSpecies Animal::getSpecies() const {
    return species;
}

std::string Animal::getSpeciesName() const {
    switch (species) {
        case WOLF:
            return "Wolf";
        case SHEEP:
            return "Sheep";
        case FOX:
            return "Fox";
        case TURTLE:
            return "Turtle";
        case ANTELOPE:
            return "Antelope";
        case HUMAN:
            return "Human";
        default:
            return "Unknown species";
    }
}

void Animal::moveTo(int x, int y) {
    if (x >= 0 && x < this->getWorld()->getWidth() && y >= 0 && y < this->getWorld()->getHeight()) {
        this->setPositionX(x);
        this->setPositionY(y);
    } else {
        std::cerr << "Invalid move to (" << x << ", " << y << ")" << std::endl;
    }
}

void Animal::moveRandomly() {
    const int worldWidth = this->getWorld()->getWidth();
    const int worldHeight = this->getWorld()->getHeight();

    int newX = this->getPositionX();
    int newY = this->getPositionY();

    bool moved = false;
    while (!moved) {
        switch (int direction = std::rand() % 4) {
            case 0:
                if (newY > 0) {
                    newY--;
                    moved = true;
                }
                break;
            case 1:
                if (newY < worldHeight - 1) {
                    newY++;
                    moved = true;
                }
                break;
            case 2:
                if (newX > 0) {
                    newX--;
                    moved = true;
                }
                break;
            case 3:
                if (newX < worldWidth - 1) {
                    newX++;
                    moved = true;
                }
                break;
        }
    }
    // Move the animal to the new position
    this->moveTo(newX, newY);
}

void Animal::action() {
    moveRandomly();

    /*// Check for collisions with other organisms
    for (const auto& organism : this->getWorld()->getOrganisms()) {
        if (organism->isAlive() && organism != this) {
            if (this->getPositionX() == organism->getPositionX() &&
                this->getPositionY() == organism->getPositionY()) {
                collision(organism.get());
            }
        }
    }*/
}

void Animal::collision(Organism* other) {
    // Implement the collision logic for the animal
}

