#include <iostream>
#include <memory>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "GameManager.h"
#include "World.h"
#include "Organism/Animal/Human.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main(int argc, char* argv[]) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const std::unique_ptr<GameManager> game_manager(new GameManager());
    World* world = game_manager->createWorld();

    while (const int key = getch()) {
        if (key == 27) { // ESC key
            break;
        }

        switch (key) {
            case 't':
                world->makeTurn();
                break;
            case KEY_UP:
                game_manager->setPlayerDirection(UP);
                break;
            case KEY_DOWN:
                game_manager->setPlayerDirection(DOWN);
                break;
            case KEY_LEFT:
                game_manager->setPlayerDirection(LEFT);
                break;
            case KEY_RIGHT:
                game_manager->setPlayerDirection(RIGHT);
                break;
            case 'p':
                world->getPlayer()->activateAbility();
                break;
            case 's':
                game_manager->saveWorldToFile(argv[0]);
                break;
            case 'n':
                game_manager->deleteWorld();
                world = game_manager->createWorld();
                break;
            case 'l':
                world = game_manager->loadWorld(argv[0], world);
                break;
            default:
                break;
        }

        world->draw();
    }
}
