//
// Created by Wiktor on 14.04.2025.
//

#ifndef GRASS_H
#define GRASS_H
#include "Plant.h"


class Grass final : public Plant {
public:
    Grass(Position position, World *world);
    ~Grass() override;

    [[nodiscard]] std::unique_ptr<Plant> makeChild() const override;

    void draw() override;
};



#endif //GRASS_H
