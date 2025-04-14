//
// Created by Wiktor on 14.04.2025.
//

#ifndef ANTELOPE_H
#define ANTELOPE_H
#include "Animal.h"


class Antelope final : public Animal {
public:
    Antelope(Position position, World *world);
    ~Antelope() override;

    [[nodiscard]] std::unique_ptr<Animal> makeChild() const override;

    void draw() override;

    void makeMove() override;
    void collision(Organism* other) override;
    bool defendAttack(Organism* attacker) override;
};



#endif //ANTELOPE_H
