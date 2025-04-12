//
// Created by Wiktor on 12.04.2025.
//

#include "Organism.h"

Organism::Organism(const int x, const int y, const int age, const int strength, const int initiative)
        : x(x), y(y), age(age), strength(strength), initiative(initiative), alive(true) {}

Organism::~Organism() = default;
