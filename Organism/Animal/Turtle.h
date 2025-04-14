//
// Created by Wiktor on 14.04.2025.
//

#ifndef TURTLE_H
#define TURTLE_H
#include "Animal.h"


class Turtle final : public Animal {
public:
    Turtle(Position position, World *world);
    ~Turtle() override;

    [[nodiscard]] std::unique_ptr<Animal> makeChild() const override;
    void makeMove() override;

    void attack(Animal* other) override;
    bool defendAttack(Organism* attacker) override;

    void draw() override;
};



#endif //TURTLE_H
