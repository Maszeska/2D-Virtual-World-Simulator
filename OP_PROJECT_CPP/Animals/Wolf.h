//
// Created by Marta on 18/04/2024.
//

#ifndef OP_PROJECT_CPP_WOLF_H
#define OP_PROJECT_CPP_WOLF_H

#define WOLF_CHAR 'W'
#define WOLF_STRENGTH 9
#define WOLF_INIT 5

#include "../Animal.h"

class Wolf : public Animal {
public:
    Wolf(Position& position, World* world);
};

Wolf::Wolf(Position& position, World* world)
        : Animal(WOLF_STRENGTH, WOLF_INIT, position, world, WOLF_CHAR) {}


#endif //OP_PROJECT_CPP_WOLF_H
