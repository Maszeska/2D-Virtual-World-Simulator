//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_GRASS_H
#define OP_PROJECT_CPP_GRASS_H

#define GRASS_CHAR '^'
#define GRASS_STRENGTH 0

#include "../Plant.h"

class Grass : public Plant {
public:
    Grass( Position& position, World* world);
};

Grass::Grass( Position& position, World* world)
        : Plant(GRASS_STRENGTH, position, world, GRASS_CHAR) {}



#endif //OP_PROJECT_CPP_GRASS_H
