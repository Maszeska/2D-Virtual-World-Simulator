//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_ANTELOPE_H
#define OP_PROJECT_CPP_ANTELOPE_H

#define ANTELOPE_CHAR 'A'
#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INIT 4

#include "../Animal.h"

class Antelope : public Animal {
public:
    Antelope(Position& position, World* world);
    void action() override;
};

Antelope::Antelope( Position& position, World* world)
        : Animal(ANTELOPE_STRENGTH, ANTELOPE_INIT, position, world, ANTELOPE_CHAR) {}



void Antelope::action() {
    // Generate a random direction for movement
    int direction = rand() % 4;
    Position newPosition = position;
    switch (direction) {
        case 0: // Move up
            newPosition.y -= 2;
            break;
        case 1: // Move down
            newPosition.y += 2;
            break;
        case 2: // Move left
            newPosition.x -= 2;
            break;
        case 3: // Move right
            newPosition.x += 2;
            break;
        default:
            break;
    }

    if (newPosition.x >= 0 && newPosition.x < world->getWidth() &&
        newPosition.y >= 0 && newPosition.y < world->getHeight()) {
        if (world->map[newPosition.y][newPosition.x] != nullptr) {
            collision(world->map[newPosition.y][newPosition.x]);
        } else {
            Organism* temp = this->world->map[position.y][position.x];
            this->world->map[position.y][position.x] = nullptr;
            position = newPosition;
            this->world->map[position.y][position.x] = temp;
        }
    }
}


#endif //OP_PROJECT_CPP_ANTELOPE_H
