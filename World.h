//
// Created by Wiktor on 12.04.2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <vector>
#include <string>

#include "Organism/Organism.h"

class Organism;

class World {
private:
    int width;
    int height;

    std::vector<std::unique_ptr<Organism>> organisms;
    std::vector<std::unique_ptr<Organism>> new_organisms;
    std::vector<std::string> world_messages;
    void mergeNewOrganisms();
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
    [[nodiscard]] const std::vector<std::unique_ptr<Organism>>& getOrganisms() const;
    [[nodiscard]] bool isFieldEmpty(int x, int y) const;

    void removeDeadOrganisms();
    void makeTurn();
    void draw();

    void addMessage(const std::string& message);
    void clearMessages();
    void displayMessages() const;
};



#endif //WORLD_H
