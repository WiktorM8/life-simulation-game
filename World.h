//
// Created by Wiktor on 12.04.2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <vector>
#include <string>

#include "GameManager.h"
#include "Organism/Organism.h"

class Organism;
class GameManager;
class Human;

class World {
    friend class GameManager;
private:
    int width;
    int height;

    std::vector<std::unique_ptr<Organism>> organisms;
    std::vector<std::unique_ptr<Organism>> new_organisms;
    std::vector<std::string> world_messages;
    GameManager* game_manager;
    void mergeNewOrganisms();
    void loadAnimal(std::ifstream &file);
    void loadPlant(std::ifstream &file);
public:
    World(int width, int height, GameManager* game_manager);
    ~World();

    void setGameManager(GameManager* game_manager);
    [[nodiscard]] GameManager* getGameManager() const;
    void clearWorld();

    void setWidth(int width);
    void setHeight(int height);
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    void addOrganism(std::unique_ptr<Organism> organism);
    void sortOrganisms();
    void generateStartingOrganisms();
    [[nodiscard]] const std::vector<std::unique_ptr<Organism>>& getOrganisms() const;
    [[nodiscard]] bool isFieldEmpty(int x, int y) const;
    [[nodiscard]] Human* getPlayer() const;

    void removeDeadOrganisms();
    void makeTurn();
    void draw();

    void addMessage(const std::string& message);
    void clearMessages();
    void displayMessages() const;

    void saveToFile(std::ofstream &file) const;
    void loadFromFile(std::ifstream &file);
};



#endif //WORLD_H
