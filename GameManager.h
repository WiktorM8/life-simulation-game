//
// Created by Wiktor on 12.04.2025.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H



class GameManager {
public:
    GameManager();
    ~GameManager() = default;

    World* createWorld();
};



#endif //GAMEMANAGER_H
