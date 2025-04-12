//
// Created by Wiktor on 12.04.2025.
//

#ifndef ORGANISM_H
#define ORGANISM_H



class Organism {
private:
    int x;
    int y;
    int age;
    int strength;
    int initiative;
    bool alive;
public:
    Organism(int x, int y, int age, int strength, int initiative);
    ~Organism();
};



#endif //ORGANISM_H
