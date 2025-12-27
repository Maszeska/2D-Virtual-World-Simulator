//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_GUARANA_H
#define OP_PROJECT_CPP_GUARANA_H

#define GUARANA_CHAR '%'
#define GUARANA_STRENGTH 0

#include "../Plant.h"

class Guarana : public Plant {
public:
    Guarana(Position& position, World* world);
};

Guarana::Guarana( Position& position, World* world)
        : Plant(GUARANA_STRENGTH, position, world, GUARANA_CHAR) {}


#endif //OP_PROJECT_CPP_GUARANA_H
