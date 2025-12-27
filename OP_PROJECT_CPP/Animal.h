#ifndef OP_PROJECT_CPP_ANIMAL_H
#define OP_PROJECT_CPP_ANIMAL_H


#include "Organism.h"

class Animal : public Organism {
public:
    Animal(int strength, int initiative, Position& position, World* world, const char& symbol);
    virtual ~Animal();
    void action() override;
    OrganismGroup getType() const override { return ANIMAL; }
};

Animal::Animal(int strength, int initiative, Position& position, World* world, const char& symbol)
        : Organism(strength, initiative, position, world, symbol) {}

Animal::~Animal() {}

void Animal::action() {
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
        if (world->map[newPosition.y][newPosition.x] != nullptr) {
            collision(world->map[newPosition.y][newPosition.x]);
        }
        else {
            Organism* temp = this->world->map[position.y][position.x];
            this->world->map[position.y][position.x] = nullptr;
            position = newPosition;
            this->world->map[position.y][position.x] = temp;
        }
    }
}



#endif //OP_PROJECT_CPP_ANIMAL_H
