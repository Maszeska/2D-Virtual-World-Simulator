#ifndef OP_PROJECT_CPP_HUMAN_H
#define OP_PROJECT_CPP_HUMAN_H

#define HUMAN_CHAR '@'
#define HUMAN_STRENGTH 5
#define HUMAN_INIT 4

#include "../Animal.h"

class Human : public Animal {
public:
    Human(Position& position, World* world);
    void action() override;
};

Human::Human( Position& position, World* world)
        : Animal(HUMAN_STRENGTH, HUMAN_INIT, position, world, HUMAN_CHAR) {}

void Human::action() {
    refresh();
    if ( world->getCooldown() == 10) {
        strength = strength + 5;
    } else if (world->getCooldown() >= 5){
        --strength;
    }

    char nextMove = world->getNextMove();
    Position newPosition = position;

    switch (nextMove) {
        case 'w':
            newPosition.y--;
            break;
        case 's':
            newPosition.y++;
            break;
        case 'a':
            newPosition.x--;
            break;
        case 'd':
            newPosition.x++;
            break;
        default:
            break;
    }

    Organism* temp = this->world->map[position.y][position.x];
    if (newPosition.x >= 0 && newPosition.x < world->getWidth() &&
        newPosition.y >= 0 && newPosition.y < world->getHeight()) {
        if (world->map[newPosition.y][newPosition.x] != nullptr) {
            collision(world->map[newPosition.y][newPosition.x]);
        } else {
            this->world->map[position.y][position.x] = nullptr;
            position = newPosition;
            this->world->map[position.y][position.x] = temp;
        }
    }
}



#endif // OP_PROJECT_CPP_HUMAN_H
