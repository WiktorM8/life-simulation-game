//
// Created by Wiktor on 15.04.2025.
//

#ifndef HUMAN_H
#define HUMAN_H
#include "Animal.h"

#define ABILITY_COOLDOWN 5
#define ABILITY_EXPIRATION_TIME 5

class Human final : public Animal {
private:
    int abilityCooldown;
    int abilityExpirationTime;
    bool abilityActive;
public:
    Human(Position position, World* world);
    ~Human() override;

    [[nodiscard]] std::unique_ptr<Animal> makeChild() const override;
    void draw() override;
    void makeMove() override;
    void action() override;
    void collision(Organism *other) override;
    bool defendAttack(Organism *attacker) override;

    void setAlive(bool alive) override;

    void activateAbility();
    void setAbilityCooldown(int cooldown);
    [[nodiscard]] int getAbilityCooldown() const;

    void setAbilityExpirationTime(int time);
    [[nodiscard]] int getAbilityExpirationTime() const;

    void setAbilityActive(bool active);
    [[nodiscard]] bool isAbilityActive() const;

    void saveToFile(std::ofstream &file) const override;
};



#endif //HUMAN_H
