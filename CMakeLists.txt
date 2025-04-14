cmake_minimum_required(VERSION 3.29)
project(LifeSimulationGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(LifeSimulationGame main.cpp
        World.cpp
        GameManager.cpp
        Organism/Organism.cpp
        definitions.h
        Organism/Animal/Animal.cpp
        Organism/Animal/Wolf.cpp
        Organism/Animal/Sheep.cpp
        Organism/Animal/Fox.cpp
        Organism/Animal/Turtle.cpp
        Organism/Animal/Antelope.cpp
)
