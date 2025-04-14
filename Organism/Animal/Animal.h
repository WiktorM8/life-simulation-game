//
// Created by Wiktor on 12.04.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H

#include <optional>
#include <string>

#include "../Organism.h"

#define BREED_COOLDOWN 3

enum AnimalSpecies {
    WOLF,
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    HUMAN
};

class Animal: public Organism {
private:
    AnimalSpecies species;
    Position lastPosition{};

    int breedCooldown;
protected:
    virtual void makeMove();
    void checkForCollisions();
    virtual void attack(Animal* other);
    void breed(Animal *other);
public:
    Animal(Position position, int strength, int initiative, AnimalSpecies species, World* world);
    ~Animal() override;

    void setSpecies(AnimalSpecies species);
    [[nodiscard]] AnimalSpecies getSpecies() const;
    [[nodiscard]] std::string getSpeciesName() const;

    void setBreedCooldown(int cooldown);
    void decrementBreedCooldown();
    [[nodiscard]] bool isReadyToBreed() const;
    [[nodiscard]] int getBreedCooldown() const;
    [[nodiscard]] std::optional<Position> getRandomFreePosition() const;
    void moveTo(int x, int y);
    void moveTo(Position position);

    [[nodiscard]] virtual std::unique_ptr<Animal> makeChild() const = 0;

    void setLastPosition(Position position);
    [[nodiscard]] Position getLastPosition() const;

    void action() override;
    void collision(Organism* other) override;
    /**
    * Check if the animal can attack the other organism
    * If true, then collision in this should not be called
    */
    bool defendAttack(Organism* attacker) override;
};



#endif //ANIMAL_H
