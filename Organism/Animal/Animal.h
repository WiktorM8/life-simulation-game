//
// Created by Wiktor on 12.04.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

#include "../Organism.h"

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
public:
    Animal(int x, int y, int strength, int initiative, AnimalSpecies species, World* world);
    ~Animal() override;

    void setSpecies(AnimalSpecies species);
    [[nodiscard]] AnimalSpecies getSpecies() const;
    [[nodiscard]] std::string getSpeciesName() const;

    void action() override;
    void collision(Organism* other) override;
};



#endif //ANIMAL_H
