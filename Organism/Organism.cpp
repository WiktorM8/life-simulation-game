//
// Created by Wiktor on 12.04.2025.
//

#include "Organism.h"

Organism::Organism(const int x, const int y, const int strength, const int initiative,
                  const OrganismType type, World* world)
        : positionX(x), positionY(y), strength(strength), initiative(initiative), alive(true),
          type(type), world(world) {
    this->age = 0;
}

Organism::~Organism() = default;

/**
 * Setters and Getters
 */
void Organism::setPositionX(const int x) {
    this->positionX = x;
}
void Organism::setPositionY(const int y) {
    this->positionY = y;
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
    return positionX;
}
int Organism::getPositionY() const {
    return positionY;
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
World* Organism::getWorld() const {
    return world;
}




