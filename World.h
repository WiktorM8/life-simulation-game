//
// Created by Wiktor on 12.04.2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <vector>

#include "Organism/Organism.h"

class Organism;

class World {
private:
    int width;
    int height;

    std::vector<std::unique_ptr<Organism>> organisms;
public:
    World(int width, int height);
    ~World();

    void setWidth(int width);
    void setHeight(int height);
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    void addOrganism(std::unique_ptr<Organism> organism);
    void sortOrganisms();
    void generateStartingOrganisms();

    void removeDeadOrganisms();
    void makeTurn();
    void draw();
};



#endif //WORLD_H
