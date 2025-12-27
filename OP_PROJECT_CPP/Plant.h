//
// Created by Marta on 11/04/2024.
//

#ifndef OP_PROJECT_CPP_PLANT_H
#define OP_PROJECT_CPP_PLANT_H

#include "Organism.h"
#define PLANT_INIT 0

class Plant : public Organism {
public:
    Plant(int strength, Position& position, World* world, const char& symbol);
    ~Plant();
    void action() override;
    OrganismGroup getType() const override { return PLANT; }
};

Plant::Plant(int strength, Position& position, World* world, const char& symbol)
        : Organism(strength, PLANT_INIT, position, world, symbol) {}

Plant::~Plant() {}

void Plant::action() {
    int pr = 15;
    int probability = rand() % 100;

    if (probability < pr) {
        int direction = rand() % 4;
        Position newPosition = position;

        switch (direction) {
            case 0: // Move up
                newPosition.y--;
                break;
            case 1: // Move down
                newPosition.y++;
                break;
            case 2: // Move left
                newPosition.x--;
                break;
            case 3: // Move right
                newPosition.x++;
                break;
            default:
                break;
        }

        if (newPosition.x >= 0 && newPosition.x < world->getWidth() &&
            newPosition.y >= 0 && newPosition.y < world->getHeight() &&
            world->map[newPosition.y][newPosition.x] == nullptr) {

            auto* newPlant = new Plant(strength, newPosition, world, symbol);
            world->map[newPosition.y][newPosition.x] = newPlant;
            world->organisms.push_back(newPlant);
        }
    }
}


#endif //OP_PROJECT_CPP_PLANT_H
