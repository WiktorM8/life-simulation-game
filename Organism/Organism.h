//
// Created by Wiktor on 12.04.2025.
//

#ifndef ORGANISM_H
#define ORGANISM_H
#include "../World.h"

enum OrganismType {
    ANIMAL,
    PLANT
};

typedef struct {
    int x;
    int y;
} Position;

class World;

class Organism {
private:
    Position position;
    int age;
    int strength;
    int initiative;
    bool alive;
    OrganismType type;
    World* world;
public:
    Organism(Position position, int strength, int initiative, OrganismType type, World* world);
    virtual ~Organism();

    void setPositionX(int x);
    void setPositionY(int y);
    void setPosition(Position position);
    void setAge(int age);
    void incrementAge();
    void setStrength(int strength);
    void setInitiative(int initiative);
    void setAlive(bool alive);
    void setType(OrganismType type);
    void setWorld(World* world);

    [[nodiscard]] int getPositionX() const;
    [[nodiscard]] int getPositionY() const;
    [[nodiscard]] Position getPosition() const;
    [[nodiscard]] int getAge() const;
    [[nodiscard]] int getStrength() const;
    [[nodiscard]] int getInitiative() const;
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] OrganismType getType() const;
    [[nodiscard]] World* getWorld() const;

    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    /**
   * Check if the animal can attack the other organism
   * If false, then collision in this should not be called
   */
    virtual bool defendAttack(Organism* attacker) = 0;
    virtual void draw() = 0;
};



#endif //ORGANISM_H
