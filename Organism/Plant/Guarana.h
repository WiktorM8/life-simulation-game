//
// Created by Wiktor on 14.04.2025.
//

#ifndef GUARANA_H
#define GUARANA_H
#include "Plant.h"


class Guarana final : public Plant {
public:
    Guarana(Position position, World *world);
    ~Guarana() override;

    [[nodiscard]] std::unique_ptr<Plant> makeChild() const override;

    void draw() override;
    void collision(Organism* other) override;
};



#endif //GUARANA_H
