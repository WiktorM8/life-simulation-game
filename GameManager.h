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
public:
    GameManager();
    ~GameManager() = default;

    World* createWorld();

    void setPlayerDirection(PlayerDirection direction);
    [[nodiscard]] PlayerDirection getPlayerDirection() const;
    void printPlayerDirection() const;

    void setPlayerAlive(bool alive);
    [[nodiscard]] bool isPlayerAlive() const;
};



#endif //GAMEMANAGER_H
