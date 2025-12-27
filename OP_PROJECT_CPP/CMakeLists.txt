cmake_minimum_required(VERSION 3.26)
project(OP_PROJECT_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(OP_PROJECT_CPP main.cpp
        Plant.h
        Organism.h
        Animal.h
        Animals/Human.h
        World.h
        Organism.cpp
        Position.h
        World.cpp
        Organism.cpp
        Animals/Wolf.h
        Animals/Sheep.h
        Animals/Fox.h
        Animals/Turtle.h
        Animals/Antelope.h
        Plants/Grass.h
        Plants/Sow_thistle.h
        Plants/Guarana.h
        Plants/Belladonna.h
        Plants/Sosnowsky_Hogweed.h
)

find_package(Curses REQUIRED)
target_link_libraries(OP_PROJECT_CPP ${CURSES_LIBRARIES})