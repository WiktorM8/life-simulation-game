//
// Created by Wiktor on 14.04.2025.
//

#ifndef PLANT_H
#define PLANT_H
#include "../Organism.h"

enum PlantSpecies {
    GRASS,
    DANDELION,
    GUARANA,
    WOLF_BERRY,
    SOSNOWSKY_HOGWEED
};

class Plant : public Organism {
private:
    PlantSpecies species;
protected:
    void spread() const;
public:
    Plant(Position position, int strength, int initiative, PlantSpecies species, World* world);
    ~Plant() override;

    void setSpecies(PlantSpecies species);
    [[nodiscard]] PlantSpecies getSpecies() const;
    [[nodiscard]] std::string getSpeciesName() const;

    [[nodiscard]] virtual std::unique_ptr<Plant> makeChild() const = 0;

    void action() override;
    void collision(Organism* other) override;
};



#endif //PLANT_H
