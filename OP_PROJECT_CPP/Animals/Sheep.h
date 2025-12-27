//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_SHEEP_H
#define OP_PROJECT_CPP_SHEEP_H

#define SHEEP_CHAR 'S'
#define SHEEP_STRENGTH 4
#define SHEEP_INIT 4

#include "../Animal.h"

class Sheep : public Animal {
public:
    Sheep(Position& position, World* world);
};

Sheep::Sheep( Position& position, World* world)
        : Animal(SHEEP_STRENGTH, SHEEP_INIT, position, world, SHEEP_CHAR) {}


#endif //OP_PROJECT_CPP_SHEEP_H
