#include "World.h"
#include "Animals/Human.h"
#include "Animals/Wolf.h"
#include "Animals/Sheep.h"
#include "Animals/Fox.h"
#include "Animals/Turtle.h"
#include "Animals/Antelope.h"
#include "Plants/Grass.h"
#include "Plants/Guarana.h"
#include "Plants/Sow_thistle.h"
#include "Plants/Belladonna.h"
#include "Plants/Sosnowsky_Hogweed.h"

#define N_HUMAN 1
#define N_WOLF 2
#define N_SHEEP 3
#define N_FOX 2
#define N_TURTLE 2
#define N_ANTELOPE 2
#define N_GRASS 3
#define N_SOW_THISTLE 2
#define N_GUARANA 2
#define N_BELLADONNA 1
#define N_SOSNOWSKY_HOGWEED 2


World::World(const int& width,const int& height) : width(width), height(height) {
    // Initialize ncurses
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    window = newwin(height+2, width+2, 1, 1);   // Create the game window
    this->createWorld();
    mvwprintw(stdscr, height+3, 2, "World created");
    printDirection();
}

World::~World() {
    // Clean up organisms vector
    for (auto& organism : organisms) {
        delete organism;
    }
    organisms.clear();

    // Clean up ncurses
    if (window != nullptr) {
        delwin(window);
        endwin();
    }
}

void World::createWorld() {
    for (int y = 0; y < height; y++) {
        map.emplace_back();
        for (int x = 0; x < width; x++) {
            map[y].push_back(nullptr);
        }
    }
    createOrganism();
}

void World::initializeOrganismCounts() {
    // Store the count of organisms for each type
    organismCounts = {
            {HUMAN, N_HUMAN},
            {WOLF, N_WOLF},
            {SHEEP, N_SHEEP},
            {FOX, N_FOX},
            {TURTLE, N_TURTLE},
            {ANTELOPE, N_ANTELOPE},
            {GRASS, N_GRASS},
            {SOW_THISTLE, N_SOW_THISTLE},
            {GUARANA, N_GUARANA},
            {BELLADONNA, N_BELLADONNA},
            {SOSNOWSKY_HOGWEED, N_SOSNOWSKY_HOGWEED}
    };
}

void World::createOrganism() {
    initializeOrganismCounts();
    for (const auto& entry : organismCounts) {
        OrganismType type = entry.first;
        int count = entry.second;
        for (int i = 0; i < count; ++i) {
            Position position = {std::rand() % height, std::rand() % width};
            do {
                position = {std::rand() % height, std::rand() % width};
            } while (map[position.y][position.x] != nullptr); // Keep generating until the position is empty
            Organism* newOrganism = nullptr;
            switch (type) {
                case HUMAN:
                    newOrganism = new Human(position, this);
                    break;
                case WOLF:
                    newOrganism = new Wolf(position, this);
                    break;
                case SHEEP:
                    newOrganism = new Sheep(position, this);
                    break;
                case FOX:
                    newOrganism = new Fox(position, this);
                    break;
                case TURTLE:
                    newOrganism = new Turtle(position, this);
                    break;
                case ANTELOPE:
                    newOrganism = new Antelope(position, this);
                    break;
                case GRASS:
                    newOrganism = new Grass(position, this);
                    break;
                case SOW_THISTLE:
                    newOrganism = new Sow_thistle(position, this);
                    break;
                case GUARANA:
                    newOrganism = new Guarana(position, this);
                    break;
                case BELLADONNA:
                    newOrganism = new Belladonna(position, this);
                    break;
                case SOSNOWSKY_HOGWEED:
                    newOrganism = new Sosnowsky_Hogweed(position, this);
                    break;
                default:
                    break;
            }
            if (newOrganism != nullptr) {
                organisms.push_back(newOrganism);
                addOrganism(position, newOrganism);
            }
        }
    }
}

void World::removeOrganism(Organism* organism) {
    auto it = std::find(organisms.begin(), organisms.end(), organism);
    if (it != organisms.end()) {
        organisms.erase(it);
        for (int i = 0; i < map.size(); ++i) {
            auto& row = map[i];
            auto mapIt = std::find(row.begin(), row.end(), organism);
            if (mapIt != row.end() && *mapIt == organism) {
                *mapIt = nullptr;
                break;
            }
        }
    }
}

void World::bornAnimal(char type) {
    Position newPos;
    do {
        newPos = {std::rand() % height, std::rand() % width};
    } while (map[newPos.y][newPos.x] != nullptr);
    Organism* newOrg = nullptr;
    switch (type) {
        case 'W':
            newOrg = new Wolf(newPos, this);
            break;
        case 'S':
            newOrg = new Sheep(newPos, this);
            break;
        case 'F':
            newOrg = new Fox(newPos, this);
            break;
        case 'T':
            newOrg = new Turtle(newPos, this);
            break;
        case 'A':
            newOrg = new Antelope(newPos, this);
            break;
        default:
            break;
    }
    if (newOrg != nullptr) {
        organisms.push_back(newOrg);
        addOrganism(newPos, newOrg);
        setInfo(getInfo() + 1);
    }
}

void World::addOrganism(const Position &position, Organism *organism) {
    if (position.x >= 0 && position.x < width && position.y >= 0 && position.y < height) {
        if (map[position.y][position.x] == nullptr) {
            map[position.y][position.x] = organism;
        } else {
            mvwprintw(stdscr, 0, 2, "Position (%d, %d) is already occupied", position.x, position.y);
            refresh();
        }
    } else {
        mvwprintw(stdscr, 0, 2, "Position (%d, %d) is outside the bounds of the map (%d,%d)", position.x, position.y, width, height);
        refresh();
    }
}

void World::draw() {
    wclear(window);
    box(window, 0, 0);
    mvwprintw(window, 0, 3, " Marta Dubowik S198320 ");
    // Print the map on the window
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == nullptr) {
                mvwaddch(window, y+1, x+1, '.'); // Print '.'
            } else {
                mvwaddch(window, y+1, x+1, map[y][x]->getSymbol()); // Print organisms
            }
        }
    }
    wrefresh(window);
}

void World::deleteMarkedOrganisms() {
    for (auto it = organisms.begin(); it != organisms.end();) {
        Organism* organism = *it;
        if (std::find(toDie.begin(), toDie.end(), organism) != toDie.end()) {
            delete organism; // Delete the organism
            it = organisms.erase(it); // Remove the pointer from the vector
        } else {
            ++it;
        }
    }
    toDie.clear(); // Clear the vector of organisms marked for deletion
}


void World::makeTurn() {
    clear();
    refresh();
    setInfo(5); // Change line in which info is printed
    for (int i = 0; i < organisms.size(); ++i) {
        if (organisms[i] != nullptr){
            organisms[i]->action(); // Call action for every Organism
        }
    }
    deleteMarkedOrganisms();
    if (cooldown != 0) {
        --cooldown;
    }
}

void World::handleInput() {
    char ch = getch();
    switch (ch) {
        case '.':   // Go to the next turn
            makeTurn();
            break;
        case 'w':
        case 's':
        case 'a':
        case 'd':
            setNextMove(ch);    // Handle arrow key input
            printDirection();
            break;
        case 'q':   // Quit the program
            endwin();
            delwin(getWindow());
            exit(0);
        case 'p': // Special power of human
            if (cooldown == 0 ){
                mvwprintw(stdscr, height+4, 2, "Human special power activated");
                cooldown = 10;
            } else {
                mvwprintw(stdscr, height+4, 2, "Not possible to activate special power for %d turns", cooldown);
            }
            refresh();
            break;
        case 'k':   // Saving to file
            saveToFile(saveFilename);
            mvwprintw(stdscr, 0, 2, "WORLD SAVED");
            refresh();
            break;
        case 'l':   // Loading from file
            loadFromFile(saveFilename);
            draw();
            mvwprintw(stdscr, 0, 2, "WORLD LOADED");
            refresh();
            break;
        default:
            break;
    }
}

void World::printDirection() {
    char dir = nextMove;
    clear();
    switch (dir) {
        case 'w':
            mvwprintw(stdscr, height+3, 2, "Human will move up");
            break;
        case 's':
            mvwprintw(stdscr, height+3, 2, "Human will move down");
            break;
        case 'a':
            mvwprintw(stdscr, height+3, 2, "Human will move left");
            break;
        case 'd':
            mvwprintw(stdscr, height+3, 2, "Human will move right");
            break;
        default:
            break;
    }
    refresh();
}

bool World::isHumanAlive() const {
    for (const auto& organism : organisms) {
        if (dynamic_cast<Human*>(organism) != nullptr) {
            return true; // Human is alive
        }
    }
    clear();
    mvwprintw(stdscr, 0, 2, "YOU LOST");
    refresh();
    return false; // Human is dead
}

void World::saveToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << width << " " << height << " " << cooldown << std::endl;
        for (const auto& row : map) {
            for (const auto& organism : row) {
                if (organism != nullptr) {
                    outFile << organism->getPosition().x << " " << organism->getPosition().y << " "
                    << organism->getSymbol() << " " << organism->getStrength() << std::endl;
                }
            }
        }
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        throw std::runtime_error("Unable to open file for writing.");
    }
}

void World::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        // Clear existing data
        for (auto& row : map) {
            for (auto& organism : row) {
                delete organism;
                organism = nullptr;
            }
            row.clear();
        }
        organisms.clear();

        inFile >> width >> height >> cooldown;
        map.resize(height, std::vector<Organism*>(width, nullptr));

        int x, y, strength;
        char typeChar;
        while (inFile >> x >> y >> typeChar >> strength) {
            Position position{y, x};
            Organism* newOrganism = nullptr;
            switch (typeChar) {
                case '@':
                    newOrganism = new Human(position, this);
                    break;
                case 'W':
                    newOrganism = new Wolf(position, this);
                    break;
                case 'S':
                    newOrganism = new Sheep(position, this);
                    break;
                case 'F':
                    newOrganism = new Fox(position, this);
                    break;
                case 'T':
                    newOrganism = new Turtle(position, this);
                    break;
                case 'A':
                    newOrganism = new Antelope(position, this);
                    break;
                case '^':
                    newOrganism = new Grass(position, this);
                    break;
                case '*':
                    newOrganism = new Sow_thistle(position, this);
                    break;
                case '%':
                    newOrganism = new Guarana(position, this);
                    break;
                case '&':
                    newOrganism = new Belladonna(position, this);
                    break;
                case '#':
                    newOrganism = new Sosnowsky_Hogweed(position, this);
                    break;
                default:
                    break;
            }
            if (newOrganism != nullptr) {
                newOrganism->setStrength(strength);
                organisms.push_back(newOrganism);
                refresh();
                addOrganism(position, newOrganism);
            }
        }
        inFile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        throw std::runtime_error("Unable to open file for reading.");
    }
}

WINDOW* World::getWindow() {
    return window;
}

int World::getCooldown() const {
    return cooldown;
}

int World::getInfo() const {
    return info;
}

void World::setInfo(int newInf) {
    info = newInf;
}

char World::getNextMove() const {
    return nextMove;
}

void World::setNextMove(char move) {
    nextMove = move;
}

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}