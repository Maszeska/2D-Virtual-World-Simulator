//
// Created by Marta on 19/04/2024.
//

#ifndef OP_PROJECT_CPP_TURTLE_H
#define OP_PROJECT_CPP_TURTLE_H

#define TURTLE_CHAR 'T'
#define TURTLE_STRENGTH 2
#define TURTLE_INIT 1

#include "../Animal.h"

class Turtle : public Animal {
public:
    Turtle(Position& position, World* world);
    void action() override;
};

Turtle::Turtle(Position& position, World* world)
        : Animal(TURTLE_STRENGTH, TURTLE_INIT, position, world, TURTLE_CHAR) {}

void Turtle::action() {
    int chance = rand() % 100;
    // If the random number is less than or equal to 75, the turtle stays in the same place
    if (chance <= 75) {
        return; // Turtle stays in the same place
    }
    Animal::action();
}


#endif //OP_PROJECT_CPP_TURTLE_H
