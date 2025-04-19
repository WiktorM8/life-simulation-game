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
    game_manager->displayMenu();
    while (const int key = getch()) {
        if (key == 27) return 0;
        if (key == 'n') {
            game_manager->createWorld();
            break;
        }
        if (key == 'l') {
            if (game_manager->loadWorld(argv[0]) != nullptr) break;
            system("cls");
            game_manager->displayMenu();
        }
    }

    while (const int key = getch()) {
        if (key == 27) { // ESC key
            break;
        }

        switch (key) {
            case 't':
                game_manager->getWorld()->makeTurn();
                break;
            case KEY_UP:
                game_manager->setPlayerDirection(UP);
                game_manager->getWorld()->makeTurn();
                break;
            case KEY_DOWN:
                game_manager->setPlayerDirection(DOWN);
                game_manager->getWorld()->makeTurn();
                break;
            case KEY_LEFT:
                game_manager->setPlayerDirection(LEFT);
                game_manager->getWorld()->makeTurn();
                break;
            case KEY_RIGHT:
                game_manager->setPlayerDirection(RIGHT);
                game_manager->getWorld()->makeTurn();
                break;
            case 'p':
                if (game_manager->getWorld()->getPlayer() != nullptr) game_manager->getWorld()->getPlayer()->activateAbility();
                break;
            case 's':
                game_manager->saveWorldToFile(argv[0]);
                break;
            case 'n':
                if (game_manager->getWorld() != nullptr) {
                    game_manager->deleteWorld();
                }
                game_manager->createWorld();
                break;
            case 'l':
                game_manager->loadWorld(argv[0]);
                break;
            default:
                break;
        }

        game_manager->getWorld()->draw();
    }
}
