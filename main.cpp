#include <iostream>
#include <memory>

#include "GameManager.h"
#include "World.h"

int main() {
    std::unique_ptr<GameManager> game_manager(new GameManager());
    std::unique_ptr<World> world(game_manager->createWorld());
}
