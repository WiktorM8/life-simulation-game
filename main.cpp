#include <iostream>
#include <memory>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "GameManager.h"
#include "World.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const std::unique_ptr<GameManager> game_manager(new GameManager());
    const std::unique_ptr<World> world(game_manager->createWorld());

    world->generateStartingOrganisms();

    while (const int key = getch()) {
        if (key == 27) { // ESC key
            break;
        }

        switch (key) {
            case 't':
                world->makeTurn();
                break;
        }

        world->draw();
    }
}
