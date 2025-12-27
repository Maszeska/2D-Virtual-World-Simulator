//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_BELLADONNA_H
#define OP_PROJECT_CPP_BELLADONNA_H

#define BELLADONNA_CHAR '&'
#define BELLADONNA_STRENGTH 99

#include "../Plant.h"

class Belladonna : public Plant {
public:
    Belladonna(Position& position, World* world);
};

Belladonna::Belladonna( Position& position, World* world)
        : Plant(BELLADONNA_STRENGTH, position, world, BELLADONNA_CHAR) {}


#endif //OP_PROJECT_CPP_BELLADONNA_H
