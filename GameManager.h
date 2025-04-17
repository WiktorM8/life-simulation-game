//
// Created by Wiktor on 12.04.2025.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "World.h"

enum PlayerDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class World;

class GameManager {
private:
    PlayerDirection playerDirection = UP;
    bool playerAlive = true;
    World *world = nullptr;
public:
    GameManager();
    ~GameManager() = default;

    World* createWorld();
    void deleteWorld();
    void saveWorldToFile(const std::string& exe_path) const;
    World* loadWorld(const std::string& exe_path, World* world);

    void setPlayerDirection(PlayerDirection direction);
    [[nodiscard]] PlayerDirection getPlayerDirection() const;
    void printPlayerDirection() const;

    void setPlayerAlive(bool alive);
    [[nodiscard]] bool isPlayerAlive() const;

    void setWorld(World* world);
    [[nodiscard]] World* getWorld() const;
};



#endif //GAMEMANAGER_H
