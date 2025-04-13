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
    void moveRandomly();
    void moveTo(int x, int y);

    int breedCooldown;
protected:
    void checkForCollisions();
    void attack(Animal* other);
    void breed(Animal *other);
public:
    Animal(int x, int y, int strength, int initiative, AnimalSpecies species, World* world);
    ~Animal() override;

    void setSpecies(AnimalSpecies species);
    [[nodiscard]] AnimalSpecies getSpecies() const;
    [[nodiscard]] std::string getSpeciesName() const;

    void setBreedCooldown(int cooldown);
    void decrementBreedCooldown();
    [[nodiscard]] bool isReadyToBreed() const;
    [[nodiscard]] int getBreedCooldown() const;
    [[nodiscard]] std::optional<std::pair<int, int>> getRandomFreePosition() const;

    [[nodiscard]] virtual std::unique_ptr<Animal> makeChild() const = 0;

    void action() override;
    void collision(Organism* other) override;
};



#endif //ANIMAL_H
