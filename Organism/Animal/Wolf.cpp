//
// Created by Wiktor on 12.04.2025.
//

#include "Wolf.h"

#include <iostream>
#include <windows.h>

Wolf::Wolf(const int x, const int y, World* world)
        : Animal(x, y, 9, 5, WOLF, world) {}

Wolf::~Wolf() = default;

void Wolf::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::cout << "W";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}


