#ifndef OP_PROJECT_CPP_ORGANISM_H
#define OP_PROJECT_CPP_ORGANISM_H

#include <ncurses.h>
#include <iostream>
#include "Position.h"

class World;

enum OrganismGroup {
    PLANT,
    ANIMAL
};

class Organism {
public:
    Organism(int strength, int initiative, Position& position, World* world, const char& symbol);
    virtual ~Organism();
    virtual void action() = 0;
    virtual void collision(Organism* defender);
    virtual OrganismGroup getType() const = 0;
    char getSymbol();
    int getStrength();
    Position getPosition();
    void setStrength(int newStr);
protected:
    int strength;
    int initiative;
    char symbol;
    Position position;
    World* world;
    bool checkEscaped(Organism* first, Organism* second);
    bool checkReflect(Organism* defender);
    void checkPowerUp(Organism* defender);
    bool checkBorn(Organism* first, Organism* second);
};

#endif // OP_PROJECT_CPP_ORGANISM_H
