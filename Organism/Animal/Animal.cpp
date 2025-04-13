//
// Created by Wiktor on 12.04.2025.
//

#include "Animal.h"

#include <iostream>
#include <optional>

Animal::Animal(const int x, const int y, const int strength, const int initiative,
               const AnimalSpecies species, World* world)
        : Organism(x, y, strength, initiative, ANIMAL, world), species(species) {
    this->breedCooldown = 0;
}

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

void Animal::setBreedCooldown(const int cooldown) {
    this->breedCooldown = cooldown;
}
int Animal::getBreedCooldown() const {
    return this->breedCooldown;
}
bool Animal::isReadyToBreed() const {
    return this->breedCooldown == 0;
}
void Animal::decrementBreedCooldown() {
    this->breedCooldown--;
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
            default:
                break;
        }
    }
    // Move the animal to the new position
    this->moveTo(newX, newY);
}

void Animal::action() {
    if (!this->isAlive()) return;
    moveRandomly();
    checkForCollisions();

    if (this->getBreedCooldown() > 0) {
        decrementBreedCooldown();
    }
}

void Animal::checkForCollisions() {
    for (const auto& organism : this->getWorld()->getOrganisms()) {
        if (organism->isAlive() && organism.get() != this) {
            if (this->getPositionX() == organism->getPositionX() &&
                this->getPositionY() == organism->getPositionY()) {
                collision(organism.get());
            }
        }
    }
}

void Animal::attack(Animal* other) {
    if (this->getStrength() >= other->getStrength()) {
        other->setAlive(false);
        this->getWorld()->addMessage("Zwierze typu " + this->getSpeciesName() + " pokonalo zwierze typu " +
                other->getSpeciesName() + " na pozycji x=" +
                std::to_string(this->getPositionX() + 1) + ", y=" +
                std::to_string(this->getPositionY() + 1));
    } else {
        this->setAlive(false);
        this->getWorld()->addMessage("Zwierze typu " + other->getSpeciesName() + " pokonalo zwierze typu " +
                this->getSpeciesName() + " na pozycji x=" +
                std::to_string(this->getPositionX() + 1) + ", y=" +
                std::to_string(this->getPositionY() + 1));
    }
}

std::optional<std::pair<int, int>> Animal::getRandomFreePosition() const {
    const int directions[4][2] = {
        {0, -1},  // góra
        {0, 1},   // dół
        {-1, 0},  // lewo
        {1, 0}    // prawo
    };

    std::vector<std::pair<int, int>> freePositions;

    for (const auto& dir : directions) {
        int newX = this->getPositionX() + dir[0];
        int newY = this->getPositionY() + dir[1];

        if (newX >= 0 && newX < this->getWorld()->getWidth() &&
            newY >= 0 && newY < this->getWorld()->getHeight() &&
            this->getWorld()->isFieldEmpty(newX, newY)) {
            freePositions.emplace_back(newX, newY);
        }
    }

    if (!freePositions.empty()) {
        const int randomIndex = std::rand() % freePositions.size();
        return freePositions[randomIndex];
    }

    return std::nullopt;
}

void Animal::breed(Animal* other) {
    if (!this->isReadyToBreed() || !other->isReadyToBreed()) {
        /*this->getWorld()->addMessage("Zwierzeta typu " + this->getSpeciesName() +
            " nie sa gotowe do rozmnozenia na pozycji x=" + std::to_string(this->getPositionX() + 1) +
            ", y=" + std::to_string(this->getPositionY() + 1));*/
        return;
    }
    const auto freePosition = this->getRandomFreePosition();
    if (freePosition == std::nullopt) {
        this->getWorld()->addMessage("Zwierzeta typu " + this->getSpeciesName() +
            " nie znalazly miejsca do rozmnozenia na pozycji x=" + std::to_string(this->getPositionX() + 1) +
            ", y=" + std::to_string(this->getPositionY() + 1));
        return;
    }

    auto child = this->makeChild();
    child->setPositionX(freePosition->first);
    child->setPositionY(freePosition->second);
    child->setBreedCooldown(BREED_COOLDOWN);
    this->getWorld()->addOrganism(std::move(child));

    this->setBreedCooldown(BREED_COOLDOWN);
    other->setBreedCooldown(BREED_COOLDOWN);

    this->getWorld()->addMessage("Zwierzeta typu " + this->getSpeciesName() +
            " na pozycji x=" + std::to_string(this->getPositionX() + 1) +
            ", y=" + std::to_string(this->getPositionY() + 1) +
            " urodzily dziecko na pozycji x=" +
            std::to_string(freePosition->first) + ", y=" + std::to_string(freePosition->second)
            );
}

void Animal::collision(Organism* other) {
    if (other->getType() == ANIMAL) {
        if (const auto other_animal = dynamic_cast<Animal*>(other)) {
            if (this->getSpecies() == other_animal->getSpecies()) {
                breed(other_animal);
            } else {
                attack(other_animal);
            }
        }
    }
}

