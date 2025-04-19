//
// Created by Wiktor on 15.04.2025.
//

#include "Human.h"
#include "../Plant/Plant.h"

#include <iostream>
#include <windows.h>

Human::Human(const Position position, World *world)
        : Animal(position, 5, 4, HUMAN, world) {
    this->abilityActive = false;
    this->abilityCooldown = 0;
    this->abilityExpirationTime = 0;
    world->getGameManager()->setPlayerAlive(true);
}

Human::~Human() = default;

std::unique_ptr<Animal> Human::makeChild() const {
    const auto human = new Human(this->getPosition(), this->getWorld());
    return std::unique_ptr<Animal>(human);
}

void Human::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (7 << 4));
    std::cout << "H";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Human::makeMove() {
    const int worldWidth = this->getWorld()->getWidth();
    const int worldHeight = this->getWorld()->getHeight();

    const PlayerDirection playerDirection = this->getWorld()->getGameManager()->getPlayerDirection();

    int newX = this->getPositionX();
    int newY = this->getPositionY();

    switch (playerDirection) {
        case UP:
            newY--;
            break;
        case DOWN:
            newY++;
            break;
        case LEFT:
            newX--;
            break;
        case RIGHT:
            newX++;
            break;
    }

    if (newX >= 0 && newX < worldWidth && newY >= 0 && newY < worldHeight) {
        this->moveTo(newX, newY);
    } else {
        this->getWorld()->addMessage("Czlowiek nie moze wyjsc poza granice mapy!");
    }
}

void Human::action() {
    if (!this->isAlive()) return;

    makeMove();
    checkForCollisions();
    incrementAge();

    if (this->getAbilityCooldown() > 0) {
        this->setAbilityCooldown(this->getAbilityCooldown() - 1);
    }

    if (this->getAbilityExpirationTime() > 0) {
        this->setAbilityExpirationTime(this->getAbilityExpirationTime() - 1);
        if (this->getAbilityExpirationTime() == 0) {
            this->setAbilityActive(false);
            this->setAbilityCooldown(ABILITY_COOLDOWN);
            this->getWorld()->addMessage("Umiejetnosc czlowieka sie wyczerpala");
        }
    }
}

void Human::collision(Organism *other) {
    if (this->isAbilityActive()) {
        if (other->getType() == ANIMAL && other->getStrength() > this->getStrength()) {
            this->getWorld()->addMessage("Czlowiek ucieka przed walka");
            this->moveTo(this->getLastPosition());
            return;
        }
    }
    Animal::collision(other);
}

bool Human::defendAttack(Organism *attacker) {
    if (this->isAbilityActive()) {
        if (attacker->getType() == PLANT) {
            if (const auto plant_attacker = dynamic_cast<Plant *>(attacker)) {
                this->getWorld()->addMessage("Czlowiek zjada rosline " + plant_attacker->getSpeciesName() +
                                             " ale nic mu sie nie stalo dzieki umiejetnosci");
            }
            return true;
        }

        const auto animal_attacker = dynamic_cast<Animal *>(attacker);
        if (!animal_attacker) {
            return true;
        }

        this->getWorld()->addMessage("Umiejetnosc czlowieka zablokowala atak");
        std::optional<Position> new_position = this->getRandomFreePosition();
        if (!new_position.has_value()) {
            animal_attacker->moveTo(animal_attacker->getLastPosition());
            return true;
        }
        this->moveTo(new_position.value());
        return true;
    }
    return false;
}

void Human::activateAbility() {
    if (this->getAbilityCooldown() == 0 && !this->isAbilityActive()) {
        this->setAbilityActive(true);
        this->setAbilityExpirationTime(ABILITY_EXPIRATION_TIME);
        this->getWorld()->addMessage("Umiejetnosc czlowieka zostala aktywowana");
    } else if (this->isAbilityActive()) {
        this->getWorld()->addMessage("Umiejetnosc czlowieka jest aktywna, pozostalo: " +
                                            std::to_string(this->getAbilityExpirationTime()) + " tur");
    } else {
        this->getWorld()->addMessage("Umiejetnosc czlowieka jest w trakcie odnowienia, pozostalo: " +
                                     std::to_string(this->getAbilityCooldown()) + " tur");
    }
}

void Human::setAlive(const bool alive) {
    if (alive) {
        this->getWorld()->getGameManager()->setPlayerAlive(true);
    } else {
        this->getWorld()->getGameManager()->setPlayerAlive(false);
    }
    Organism::setAlive(alive);
}

void Human::setAbilityCooldown(const int cooldown) {
    this->abilityCooldown = cooldown;
}
int Human::getAbilityCooldown() const {
    return this->abilityCooldown;
}
void Human::setAbilityExpirationTime(const int time) {
    this->abilityExpirationTime = time;
}
int Human::getAbilityExpirationTime() const {
    return this->abilityExpirationTime;
}
void Human::setAbilityActive(const bool active) {
    this->abilityActive = active;
}
bool Human::isAbilityActive() const {
    return this->abilityActive;
}

void Human::saveToFile(std::ofstream& file) const {
    file << this->getTypeName() << " " << this->getSpeciesName() << " " << this->getPositionX() << " " << this->getPositionY() << " "
        << this->getLastPosition().x << " " << this->getLastPosition().y << " "
        << this->getStrength() << " " << this->getInitiative() << " " << this->getAge() << " "
        << this->getBreedCooldown() << " " << this->isAbilityActive() << " "
        << this->getAbilityExpirationTime() << " " << this->getAbilityCooldown() << " "
        << std::endl;
}