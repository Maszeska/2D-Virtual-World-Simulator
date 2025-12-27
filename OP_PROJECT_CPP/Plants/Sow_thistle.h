//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_SOW_THISTLE_H
#define OP_PROJECT_CPP_SOW_THISTLE_H

#define SOW_THISTLE_CHAR '*'
#define SOW_THISTLE_STRENGTH 0

#include "../Plant.h"

class Sow_thistle : public Plant {
public:
    Sow_thistle( Position& position, World* world);
    void action() override;
};

Sow_thistle::Sow_thistle(Position& position, World* world)
        : Plant(SOW_THISTLE_STRENGTH, position, world, SOW_THISTLE_CHAR) {}

void Sow_thistle::action() {
    for (int i = 0; i < 3; ++i) {
        Plant::action();
    }
}

#endif //OP_PROJECT_CPP_SOW_THISTLE_H
