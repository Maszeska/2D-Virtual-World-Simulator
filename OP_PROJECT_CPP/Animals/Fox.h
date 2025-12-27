//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_FOX_H
#define OP_PROJECT_CPP_FOX_H

#define FOX_CHAR 'F'
#define FOX_STRENGTH 3
#define FOX_INIT 7

#include "../Animal.h"

class Fox : public Animal {
public:
    Fox(Position& position, World* world);
    void action() override;
};

Fox::Fox(Position& position, World* world)
        : Animal(FOX_STRENGTH, FOX_INIT, position, world, FOX_CHAR) {}

void Fox::action() {
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
        newPosition.y >= 0 && newPosition.y < world->getHeight()) {
        // Check if the new position is not occupied by a stronger organism
        Organism* targetOrganism = world->map[newPosition.y][newPosition.x];

        if (!targetOrganism || targetOrganism->getStrength() <= strength) {
            if (world->map[newPosition.y][newPosition.x] != nullptr) {
                collision(world->map[newPosition.y][newPosition.x]);
            }
            else {
                Organism* temp = world->map[position.y][position.x];
                world->map[position.y][position.x] = nullptr;
                position = newPosition;
                world->map[position.y][position.x] = temp;
            }
        }
    }
}

#endif //OP_PROJECT_CPP_FOX_H
