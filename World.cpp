//
// Created by Wiktor on 12.04.2025.
//

#include "World.h"

#include <algorithm>
#include <iostream>
#include <conio.h>

#include "Organism/Animal/Sheep.h"
#include "Organism/Animal/Wolf.h"

World::World(const int width, const int height) : width(width), height(height) {}

World::~World() = default;

/**
 * Setters and Getters
 */
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
    for (int i = 0; i < 3; ++i) {
        addOrganism(std::make_unique<Wolf>(std::rand() % width, std::rand() % height, this));
    }
    for (int i = 0; i < 6; ++i) {
        addOrganism(std::make_unique<Sheep>(std::rand() % width, std::rand() % height, this));
    }
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
