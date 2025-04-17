//
// Created by Wiktor on 12.04.2025.
//

#include "Organism.h"

#include <optional>

Organism::Organism(const Position position, const int strength, const int initiative,
                   const OrganismType type, World* world)
        : position(position), strength(strength), initiative(initiative), alive(true),
          type(type), world(world) {
    this->age = 0;
}

Organism::~Organism() = default;

/**
 * Setters and Getters
 */
void Organism::setPositionX(const int x) {
    this->position.x = x;
}
void Organism::setPositionY(const int y) {
    this->position.y = y;
}
void Organism::setPosition(const Position position) {
    this->position = position;
}
void Organism::setAge(const int age) {
    this->age = age;
}
void Organism::incrementAge() {
    this->age++;
}
void Organism::setStrength(const int strength) {
    this->strength = strength;
}
void Organism::setInitiative(const int initiative) {
    this->initiative = initiative;
}
void Organism::setAlive(const bool alive) {
    this->alive = alive;
}
void Organism::setType(const OrganismType type) {
    this->type = type;
}
void Organism::setWorld(World* world) {
    this->world = world;
}
int Organism::getPositionX() const {
    return position.x;
}
int Organism::getPositionY() const {
    return position.y;
}
Position Organism::getPosition() const {
    return position;
}
int Organism::getAge() const {
    return age;
}
int Organism::getStrength() const {
    return strength;
}
int Organism::getInitiative() const {
    return initiative;
}
bool Organism::isAlive() const {
    return alive;
}
OrganismType Organism::getType() const {
    return type;
}
std::string Organism::getTypeName() const {
    switch (type) {
        case ANIMAL:
            return "Zwierze";
        case PLANT:
            return "Roslina";
        default:
            return "Nieznany typ organizmu";
    }
}
OrganismType Organism::getTypeFromName(const std::string& name) {
    if (name == "Zwierze") return ANIMAL;
    if (name == "Roslina") return PLANT;
    return ANIMAL;
}
World* Organism::getWorld() const {
    return world;
}

std::optional<Position> Organism::getRandomFreePosition() const {
    const int directions[4][2] = {
        {0, -1},  // up
        {0, 1},   // down
        {-1, 0},  // left
        {1, 0}    // right
    };

    std::vector<Position> freePositions;

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


