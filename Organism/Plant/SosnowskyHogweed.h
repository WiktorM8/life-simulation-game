//
// Created by Wiktor on 14.04.2025.
//

#ifndef SOSNOWSKYHOGWEED_H
#define SOSNOWSKYHOGWEED_H
#include "Plant.h"


class SosnowskyHogweed final : public Plant {
private:
    void killNearbyAnimals();
public:
    SosnowskyHogweed(Position position, World *world);
    ~SosnowskyHogweed() override;

    [[nodiscard]] std::unique_ptr<Plant> makeChild() const override;

    void draw() override;
    void collision(Organism* other) override;
    void action() override;
};



#endif //SOSNOWSKYHOGWEED_H
