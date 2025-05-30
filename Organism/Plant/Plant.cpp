//
// Created by Wiktor on 14.04.2025.
//

#include "Plant.h"
#include "../Animal/Animal.h"

#include <iostream>

Plant::Plant(const Position position, const int strength, const int initiative, const PlantSpecies species, World* world)
        : Organism(position, strength, initiative, PLANT, world) {
    this->species = species;
}

Plant::~Plant() = default;

void Plant::setSpecies(const PlantSpecies species) {
    this->species = species;
}
PlantSpecies Plant::getSpecies() const {
    return species;
}
std::string Plant::getSpeciesName() const {
    switch (species) {
        case GRASS:
            return "Trawa";
        case DANDELION:
            return "Mlecz";
        case GUARANA:
            return "Guarana";
        case NIGHTSHADE_BERRY:
            return "Wilcza_jagoda";
        case SOSNOWSKY_HOGWEED:
            return "Barszcz_Sosnowskiego";
        default:
            return "Nieznany_gatunek_rosliny";
    }
}

PlantSpecies Plant::getSpeciesFromName(const std::string& name) {
    if (name == "Trawa") return GRASS;
    if (name == "Mlecz") return DANDELION;
    if (name == "Guarana") return GUARANA;
    if (name == "Wilcza_jagoda") return NIGHTSHADE_BERRY;
    if (name == "Barszcz_Sosnowskiego") return SOSNOWSKY_HOGWEED;
    return GRASS;
}

void Plant::action() {
    if (!this->isAlive()) return;

    this->spread();
    incrementAge();
}

void Plant::spread() const {
    const int rand = std::rand() % 100;
    if (rand >= 10) return;

    const auto freePosition = this->getRandomFreePosition();
    if (freePosition == std::nullopt) {
        return;
    }

    auto child = this->makeChild();
    child->setPositionX(freePosition->x);
    child->setPositionY(freePosition->y);
    this->getWorld()->addOrganism(std::move(child));

    /*this->getWorld()->addMessage("Roslina typu " + this->getSpeciesName() +
                                 " na pozycji x=" + std::to_string(this->getPositionX() + 1) +
                                 ", y=" + std::to_string(this->getPositionY() + 1) +
                                 " rozmnozyla sie na pozycji x=" +
                                 std::to_string(freePosition->x) + ", y=" + std::to_string(freePosition->y));*/
}

void Plant::collision(Organism* other) {
    if (other->getType() == ANIMAL) {
        this->setAlive(false);
    }
}

void Plant::saveToFile(std::ofstream& file) const {
    file << this->getTypeName() << " " << this->getSpeciesName() << " " << this->getPositionX() << " " << this->getPositionY() << " "
    << this->getStrength() << " " << this->getInitiative() << " " << this->getAge() << std::endl;
}


