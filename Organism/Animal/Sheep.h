//
// Created by Wiktor on 13.04.2025.
//

#ifndef SHEEP_H
#define SHEEP_H
#include "Animal.h"


class Sheep final : public Animal {
public:
    Sheep(Position position, World *world);
    ~Sheep() override;

    [[nodiscard]] std::unique_ptr<Animal> makeChild() const override;

    void draw() override;
};



#endif //SHEEP_H
