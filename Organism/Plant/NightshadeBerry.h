//
// Created by Wiktor on 14.04.2025.
//

#ifndef NIGHTSHADEBERRY_H
#define NIGHTSHADEBERRY_H
#include "Plant.h"


class NightshadeBerry final : public Plant {
public:
    NightshadeBerry(Position position, World *world);
    ~NightshadeBerry() override;

    [[nodiscard]] std::unique_ptr<Plant> makeChild() const override;

    void draw() override;
    void collision(Organism* other) override;
};



#endif //NIGHTSHADEBERRY_H
