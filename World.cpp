//
// Created by Wiktor on 12.04.2025.
//

#include "World.h"

#include <algorithm>
#include <iostream>
#include <conio.h>

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
    organisms.push_back(std::move(organism));
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
    for (int i = 0; i < 5; ++i) {
        addOrganism(std::make_unique<Wolf>(std::rand() % width, std::rand() % height, this));
    }
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
}
