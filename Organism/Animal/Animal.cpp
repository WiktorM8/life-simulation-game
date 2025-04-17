//
// Created by Wiktor on 12.04.2025.
//

#include "Animal.h"
#include <iostream>
#include <optional>

Animal::Animal(const Position position, const int strength, const int initiative,
               const AnimalSpecies species, World* world)
        : Organism(position, strength, initiative, ANIMAL, world), species(species) {
    this->lastPosition = position;
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
            return "Wilk";
        case SHEEP:
            return "Owca";
        case FOX:
            return "Lis";
        case TURTLE:
            return "Zolw";
        case ANTELOPE:
            return "Antylopa";
        case HUMAN:
            return "Czlowiek";
        default:
            return "Nieznany_gatunek_zwierzecia";
    }
}

AnimalSpecies Animal::getSpeciesFromName(const std::string& name) {
    if (name == "Wilk") return WOLF;
    if (name == "Owca") return SHEEP;
    if (name == "Lis") return FOX;
    if (name == "Zolw") return TURTLE;
    if (name == "Antylopa") return ANTELOPE;
    if (name == "Czlowiek") return HUMAN;
    return WOLF;
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


void Animal::moveTo(const int x, const int y) {
    if (x >= 0 && x < this->getWorld()->getWidth() && y >= 0 && y < this->getWorld()->getHeight()) {
        this->setLastPosition(this->getPosition());
        this->setPositionX(x);
        this->setPositionY(y);
    } else {
        std::cerr << "Nieprawidlowy ruch (" << x << ", " << y << ")" << std::endl;
    }
}
void Animal::moveTo(const Position position) {
    this->moveTo(position.x, position.y);
}

void Animal::makeMove() {
    const int worldWidth = this->getWorld()->getWidth();
    const int worldHeight = this->getWorld()->getHeight();

    int newX = this->getPositionX();
    int newY = this->getPositionY();

    const int axis = std::rand() % 2; // 0 - horizontal, 1 - vertical
    if (axis == 0) {
        while (true) {
            newX += (std::rand() % 3) - 1;
            if (newX >= 0 && newX < worldWidth) {
                break;
            }
        }
    } else {
        while (true) {
            newY += (std::rand() % 3) - 1;
            if (newY >= 0 && newY < worldHeight) {
                break;
            }
        }
    }

    // Move the animal to the new position
    this->moveTo(newX, newY);
}

void Animal::action() {
    if (!this->isAlive()) return;
    /*this->getWorld()->addMessage("Zwierze typu " + this->getSpeciesName() +
        " wykonuje akcje z inicjatywa " + std::to_string(this->getInitiative()) + " i wiekiem " + std::to_string(this->getAge()));*/
    makeMove();
    checkForCollisions();
    incrementAge();

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
    if (other->defendAttack(this)) {
        return;
    }

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



void Animal::breed(Animal* other) {
    if (!this->isReadyToBreed() || !other->isReadyToBreed()) {
        this->moveTo(this->getLastPosition());
        /*this->getWorld()->addMessage("Zwierzeta typu " + this->getSpeciesName() +
            " nie sa gotowe do rozmnozenia na pozycji x=" + std::to_string(this->getPositionX() + 1) +
            ", y=" + std::to_string(this->getPositionY() + 1));*/
        return;
    }
    const auto freePosition = this->getRandomFreePosition();
    if (freePosition == std::nullopt) {
        /*this->getWorld()->addMessage("Zwierzeta typu " + this->getSpeciesName() +
            " nie znalazly miejsca do rozmnozenia na pozycji x=" + std::to_string(this->getPositionX() + 1) +
            ", y=" + std::to_string(this->getPositionY() + 1));*/
        return;
    }

    auto child = this->makeChild();
    child->setPositionX(freePosition->x);
    child->setPositionY(freePosition->y);
    child->setBreedCooldown(BREED_COOLDOWN);
    this->getWorld()->addOrganism(std::move(child));

    this->setBreedCooldown(BREED_COOLDOWN);
    other->setBreedCooldown(BREED_COOLDOWN);

    this->getWorld()->addMessage("Zwierzeta typu " + this->getSpeciesName() +
            " na pozycji x=" + std::to_string(this->getPositionX() + 1) +
            ", y=" + std::to_string(this->getPositionY() + 1) +
            " urodzily dziecko na pozycji x=" +
            std::to_string(freePosition->x) + ", y=" + std::to_string(freePosition->y)
            );
}

void Animal::collision(Organism* other) {
    if (other->getType() == PLANT) {
        other->collision(this);
        return;
    }

    // If other is not a plant, then it is an animal
    if (const auto other_animal = dynamic_cast<Animal*>(other)) {
        if (this->getSpecies() == other_animal->getSpecies()) {
            breed(other_animal);
        } else {
            attack(other_animal);
        }
    }
}

bool Animal::defendAttack(Organism* attacker) {
    return false;
}

void Animal::setLastPosition(const Position position) {
    this->lastPosition = position;
}

Position Animal::getLastPosition() const {
    return this->lastPosition;
}

void Animal::saveToFile(std::ofstream& file) const {
    file << this->getTypeName() << " " << this->getSpeciesName() << " " << this->getPositionX() << " " << this->getPositionY() << " "
        << this->getLastPosition().x << " " << this->getLastPosition().y << " "
        << this->getStrength() << " " << this->getInitiative() << " " << this->getAge() << " "
        << this->getBreedCooldown() << " "
        << std::endl;
}
