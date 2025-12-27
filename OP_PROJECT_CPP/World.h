//
// Created by Marta on 11/04/2024.
//

#ifndef OP_PROJECT_CPP_WORLD_H
#define OP_PROJECT_CPP_WORLD_H

#include <ncurses.h>
#include <vector>
#include <map>
#include <fstream>
#include "Organism.h"
#include "Position.h"

enum OrganismType {
    HUMAN,
    WOLF,
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    GRASS,
    SOW_THISTLE,
    GUARANA,
    BELLADONNA,
    SOSNOWSKY_HOGWEED
};

class World {
public:
    World(const int& width,const int& height);
    ~World();
    void draw();
    void makeTurn();
    WINDOW* getWindow();
    std::vector<std::vector<Organism*> > map;
    std::vector<Organism*> organisms;
    std::vector<Organism*> toDie;
    int getWidth() const;
    int getHeight() const;
    int getInfo() const;
    void setInfo(int newInf);
    int getCooldown() const;
    void removeOrganism(Organism* organism);
    bool isHumanAlive() const;
    void bornAnimal(char type);
    void handleInput();
    char getNextMove() const;
private:
    int info = 5;
    int width;
    int height;
    char nextMove = 'd';
    int cooldown = 0;
    std::string saveFilename = "world_save.txt";
    WINDOW* window;
    std::map<OrganismType, int> organismCounts;
    void createWorld();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void setNextMove(char move);
    void printDirection();
    void createOrganism();
    void addOrganism(const Position & position, Organism * organism);
    void initializeOrganismCounts();
    void deleteMarkedOrganisms();
};

#endif //OP_PROJECT_CPP_WORLD_H
