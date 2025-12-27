#include <iostream>
#include <ncurses.h>
#include <ctime>
#include "World.h"

#define HEIGHT 10
#define WIDTH 30

int main() {
//    system("open -a Terminal OP_PROJECT_CPP"); // Open terminal window
    std::srand(std::time(nullptr));
    World world(WIDTH, HEIGHT);

    while (true) {
        world.draw();
        if (!world.isHumanAlive()) {
            break;
        }
        world.handleInput();
    }
    getch();

    // Clean up ncurses
    if (world.getWindow() != nullptr) {
        delwin(world.getWindow());
        endwin();
    }
    return 0;
}
