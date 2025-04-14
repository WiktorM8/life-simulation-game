//
// Created by Wiktor on 14.04.2025.
//

#ifndef DANDELION_H
#define DANDELION_H
#include "Plant.h"


class Dandelion final : public Plant {
public:
    Dandelion(Position position, World *world);
    ~Dandelion() override;

    [[nodiscard]] std::unique_ptr<Plant> makeChild() const override;

    void action() override;
    void draw() override;
};



#endif //DANDELION_H
