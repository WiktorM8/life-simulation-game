//
// Created by Wiktor on 12.04.2025.
//

#ifndef WOLF_H
#define WOLF_H
#include "Animal.h"  


class Wolf final : public Animal {
public:
    Wolf(Position position, World *world);
    ~Wolf() override;

    [[nodiscard]] std::unique_ptr<Animal> makeChild() const override;

    void draw() override;
};



#endif //WOLF_H
