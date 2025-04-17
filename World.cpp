//
// Created by Wiktor on 12.04.2025.
//

#include "World.h"

#include <algorithm>
#include <iostream>
#include <conio.h>

#include "Organism/Animal/Antelope.h"
#include "Organism/Animal/Fox.h"
#include "Organism/Animal/Human.h"
#include "Organism/Animal/Sheep.h"
#include "Organism/Animal/Turtle.h"
#include "Organism/Animal/Wolf.h"
#include "Organism/Plant/Dandelion.h"
#include "Organism/Plant/Grass.h"
#include "Organism/Plant/Guarana.h"
#include "Organism/Plant/NightshadeBerry.h"
#include "Organism/Plant/SosnowskyHogweed.h"

World::World(const int width, const int height, GameManager* game_manager)
    : width(width), height(height), game_manager(game_manager) {}

World::~World() = default;

/**
 * Setters and Getters
 */
void World::setGameManager(GameManager* game_manager) {
    this->game_manager = game_manager;
}
GameManager* World::getGameManager() const {
    return game_manager;
}

void World::clearWorld() {
    organisms.clear();
    new_organisms.clear();
    world_messages.clear();
    game_manager = nullptr;
}

Human* World::getPlayer() const {
    for (const auto& organism : organisms) {
        if (const auto human = dynamic_cast<Human*>(organism.get())) {
            return human;
        }
    }
    return nullptr;
}

void World::setWidth(const int width) {
    this->width = width;
}
void World::setHeight(const int height) {
    this->height = height;
}
int World::getWidth() const {
    return width;
}
int World::getHeight() const {
    return height;
}

void World::addOrganism(std::unique_ptr<Organism> organism) {
    new_organisms.emplace_back(std::move(organism));
}

void World::mergeNewOrganisms() {
    organisms.insert(organisms.end(),
                     std::make_move_iterator(new_organisms.begin()),
                     std::make_move_iterator(new_organisms.end()));
    new_organisms.clear();
}

void World::sortOrganisms() {
    std::ranges::sort(organisms,
                      [](const std::unique_ptr<Organism>& a, const std::unique_ptr<Organism>& b) {
                          if (a->getInitiative() != b->getInitiative()) {
                              return a->getInitiative() > b->getInitiative();
                          }
                          return a->getAge() > b->getAge();
                      });
}

void World::generateStartingOrganisms() {
    int size = width * height;
    for (int i = 0; i < size / 80; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Wolf>(new_position, this));
    }
    for (int i = 0; i < size / 67; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Sheep>(new_position, this));
    }
    for (int i = 0; i < size / 100; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Fox>(new_position, this));
    }
    for (int i = 0; i < size / 80; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Turtle>(new_position, this));
    }
    for (int i = 0; i < size / 100; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Antelope>(new_position, this));
    }
    for (int i = 0; i < size / 15; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Grass>(new_position, this));
    }
    for (int i = 0; i < size / 160; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Dandelion>(new_position, this));
    }
    for (int i = 0; i < size / 80; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<Guarana>(new_position, this));
    }
    for (int i = 0; i < size / 120; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<NightshadeBerry>(new_position, this));
    }
    for (int i = 0; i < size / 200; ++i) {
        Position new_position = {std::rand() % width, std::rand() % height};
        addOrganism(std::make_unique<SosnowskyHogweed>(new_position, this));
    }

    Position new_position = {std::rand() % width, std::rand() % height};
    addOrganism(std::make_unique<Human>(new_position, this));
}

const std::vector<std::unique_ptr<Organism> > &World::getOrganisms() const {
    return this->organisms;
}


void World::removeDeadOrganisms() {
    std::erase_if(
            organisms,
              [](const std::unique_ptr<Organism>& organism) {
                  return !organism->isAlive();
              }
        );
}

void World::makeTurn() {
    mergeNewOrganisms();
    sortOrganisms();

    for (const auto& organism : organisms) {
        if (organism->isAlive()) {
            organism->action();
        }
    }

    removeDeadOrganisms();
}

void World::draw() {
    system("cls");
    this->getGameManager()->printPlayerDirection();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bool empty = true;
            for (const auto& organism : organisms) {
                if (organism->getPositionX() == x && organism->getPositionY() == y) {
                    organism->draw();
                    empty = false;
                    break;
                }
            }

            if (empty) {
                std::cout << "O";
            }
        }
        std::cout << std::endl;
    }
    displayMessages();
    clearMessages();
}

bool World::isFieldEmpty(const int x, const int y) const {
    for (const auto& organism : organisms) {
        if (organism->getPositionX() == x && organism->getPositionY() == y) {
            return false;
        }
    }
    return true;
}


void World::addMessage(const std::string& message) {
    world_messages.emplace_back(message);
}

void World::clearMessages() {
    world_messages.clear();
}

void World::displayMessages() const {
    std::cout << "Wydarzenia w tej turze:" << std::endl;
    int i = 1;
    for (const auto& message : world_messages) {
        std::cout << i++ << ". " << message << std::endl;
    }
}

void World::saveToFile(std::ofstream &file) const {
    file << width << " " << height << std::endl;
    for (const auto& organism : organisms) {
        if (organism->isAlive()) {
            organism->saveToFile(file);
        }
    }
}

void World::loadFromFile(std::ifstream &file) {
    int width, height;
    file >> width >> height;
    this->setWidth(width);
    this->setHeight(height);

    while (!file.eof()) {
        std::string typeName;
        file >> typeName;
        const OrganismType type = Organism::getTypeFromName(typeName);
        if (type == ANIMAL) {
            std::string speciesName;
            file >> speciesName;
            const AnimalSpecies species = Animal::getSpeciesFromName(speciesName);
            Position position, lastPosition;
            file >> position.x >> position.y;
            file >> lastPosition.x >> lastPosition.y;
            int strength, initiative, age, breedCooldown;
            file >> strength >> initiative >> age >> breedCooldown;
            Animal *animal = nullptr;

            if (species == WOLF) {
                animal = new Wolf(position, this);
            } else if (species == SHEEP) {
                animal = new Sheep(position, this);
            } else if (species == FOX) {
                animal = new Fox(position, this);
            } else if (species == TURTLE) {
                animal = new Turtle(position, this);
            } else if (species == ANTELOPE) {
                animal = new Antelope(position, this);
            } else if (species == HUMAN) {
                auto *human = new Human(position, this);
                bool isAbilityActive;
                int abilityExpirationTime, abilityCooldown;
                file >> isAbilityActive >> abilityExpirationTime >> abilityCooldown;
                human->setAbilityActive(isAbilityActive);
                human->setAbilityExpirationTime(abilityExpirationTime);
                human->setAbilityCooldown(abilityCooldown);
                animal = human;
            }

            if (animal == nullptr) {
                continue;
            }

            animal->setLastPosition(lastPosition);
            animal->setStrength(strength);
            animal->setInitiative(initiative);
            animal->setAge(age);
            animal->setBreedCooldown(breedCooldown);
            addOrganism(std::unique_ptr<Organism>(animal));

        } else if (type == PLANT) {
            std::string speciesName;
            file >> speciesName;
            const PlantSpecies species = Plant::getSpeciesFromName(speciesName);
            Position position;
            file >> position.x >> position.y;
            int strength, initiative, age;
            file >> strength >> initiative >> age;
            Organism *organism = nullptr;

            if (species == GRASS) {
                organism = new Grass(position, this);
            } else if (species == DANDELION) {
                organism = new Dandelion(position, this);
            } else if (species == GUARANA) {
                organism = new Guarana(position, this);
            } else if (species == NIGHTSHADE_BERRY) {
                organism = new NightshadeBerry(position, this);
            } else if (species == SOSNOWSKY_HOGWEED) {
                organism = new SosnowskyHogweed(position, this);
            }

            if (organism == nullptr) {
                continue;
            }

            organism->setStrength(strength);
            organism->setInitiative(initiative);
            organism->setAge(age);
            addOrganism(std::unique_ptr<Organism>(organism));
        }
    }
}

