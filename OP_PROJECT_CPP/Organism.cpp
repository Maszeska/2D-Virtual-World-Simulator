//
// Created by Marta on 14/04/2024.
//
#include "Organism.h"
#include "World.h"

Organism::Organism(int strength, int initiative, Position& position, World* world, const char& symbol)
        : strength(strength), initiative(initiative), position(position), world(world), symbol(symbol) {}

Organism::~Organism() {}

void Organism::collision(Organism* defender){
    int attackerStrength = strength;
    int defenderStrength = defender->getStrength();
    char attackerSymbol = symbol;
    char defenderSymbol = defender->getSymbol();
    int pos = world->getInfo(); // For printing information

    bool escaped = checkEscaped(this, defender);
    bool reflected = checkReflect(defender);
    bool newborn = checkBorn(this, defender);
    checkPowerUp(defender);

    if (!escaped && !reflected && !newborn){
        if (attackerStrength >= defenderStrength) {
            // Attacker won
            mvwprintw(stdscr, world->getHeight()+pos, 2, "Organism %c eats Organism %c", attackerSymbol, defenderSymbol );
            Position attackerPosition = defender->getPosition();
            world->map[attackerPosition.y][attackerPosition.x] = this;
            world->map[position.y][position.x] = nullptr;
            position = attackerPosition;
            world->removeOrganism(defender);
            delete defender;
        } else {
            // Attacker loses
            mvwprintw(stdscr, world->getHeight()+pos, 2, "Organism %c attacked but he lost to %c", attackerSymbol, defenderSymbol);
            world->map[position.y][position.x] = nullptr;
            world->toDie.push_back(this);
        }
        int newInfo = ++pos;
        world->setInfo(newInfo);
        refresh();
    }
}


bool Organism::checkEscaped(Organism* first, Organism* second){
    // 50% change to escape from fight for antelope
    if ((first->getSymbol() == 'A' || second->getSymbol() == 'A') && (first->getSymbol() != second->getSymbol())) {
        double escapeChance = (double)rand() / RAND_MAX;
        // If the generated number is less than 0.5, antelope escapes
        if (escapeChance < 0.5) {
            mvwprintw(stdscr, world->getHeight() + world->getInfo(), 2, "Antelope escaped from the fight!");
            world->setInfo(world->getInfo()+1);
            refresh();
            return true;
        }
    }
    return false;
}

bool Organism::checkReflect(Organism* defender) {
    if (defender->getSymbol() == 'T' && this->getStrength() < 5 ) {   // Turtle reflects attack
        mvwprintw(stdscr, world->getHeight()+world->getInfo(), 2, "Turtle reflected %c", this->getSymbol());
        world->setInfo(world->getInfo()+1);
        refresh();
        return true;
    }
    return false;
}

void Organism::checkPowerUp(Organism *defender) {
    if (defender->getSymbol() == '%') {    // Increase strength of Guarana's attacker by 3
        setStrength(getStrength() + 3);
        mvwprintw(stdscr, world->getHeight()+world->getInfo(), 2, "Guarana increased strength of %c", this);
        world->setInfo(world->getInfo()+1);
        refresh();
    }
}

bool Organism::checkBorn(Organism *first, Organism *second) {
    if (first->getSymbol() == second->getSymbol() && getType() == ANIMAL){
        world->bornAnimal(first->getSymbol());
        mvwprintw(stdscr, world->getHeight()+world->getInfo(), 2, "New %c was born", first->getSymbol());
        world->setInfo(world->getInfo()+1);
        refresh();
        return true;
    }
    return false;
}

char Organism::getSymbol() {
    return symbol;
}

int Organism::getStrength() {
    return strength;
}

void Organism::setStrength(int newStr) {
    strength = newStr;
}

Position Organism::getPosition() {
    return position;
}