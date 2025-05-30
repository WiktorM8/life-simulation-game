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
    NIGHTSHADE_BERRY,
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
    [[nodiscard]] static PlantSpecies getSpeciesFromName(const std::string& name);

    [[nodiscard]] virtual std::unique_ptr<Plant> makeChild() const = 0;

    void action() override;
    void collision(Organism* other) override;

    void saveToFile(std::ofstream &file) const override;
};



#endif //PLANT_H
