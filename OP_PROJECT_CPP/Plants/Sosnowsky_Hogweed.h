//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_SOSNOWSKY_HOGWEED_H
#define OP_PROJECT_CPP_SOSNOWSKY_HOGWEED_H

#define SOSNOWSKY_HOGWEED_CHAR '#'
#define SOSNOWSKY_HOGWEED_STRENGTH 10

#include "../Plant.h"

class Sosnowsky_Hogweed : public Plant {
public:
    Sosnowsky_Hogweed(Position& position, World* world);
    void action() override;
};

Sosnowsky_Hogweed::Sosnowsky_Hogweed( Position& position, World* world)
        : Plant(SOSNOWSKY_HOGWEED_STRENGTH, position, world, SOSNOWSKY_HOGWEED_CHAR) {}

void Sosnowsky_Hogweed::action() {
    Position currentPosition = position;
    std::string killedOrganismInfo = "Sosnowsky Hogweed killed: ";

    // Iterate through all neighboring positions
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            Position neighborPosition = {currentPosition.y + dy, currentPosition.x + dx};

            if (neighborPosition.x >= 0 && neighborPosition.x < world->getWidth() &&
                neighborPosition.y >= 0 && neighborPosition.y < world->getHeight()) {
                Organism* neighborOrganism = world->map[neighborPosition.y][neighborPosition.x];

                if (neighborOrganism && neighborOrganism->getType() == ANIMAL) {
                    // Remove the neighboring animal organism
                    world->removeOrganism(neighborOrganism);
                    killedOrganismInfo += neighborOrganism->getSymbol();
                    killedOrganismInfo += " ";
                    mvwprintw(stdscr, world->getHeight()+4, 2, killedOrganismInfo.c_str());
                    delete neighborOrganism;
                }
            }
        }
    }
}



#endif //OP_PROJECT_CPP_SOSNOWSKY_HOGWEED_H
