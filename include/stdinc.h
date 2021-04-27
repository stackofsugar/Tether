#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <vector>
#include <fstream>
#include <list>

#include "orgTree.h"
#include "eventProgram.h"

template<typename Ty>
Ty input(Ty floor = std::numeric_limits<Ty>::min(), Ty ceil = std::numeric_limits<Ty>::max()) {
    Ty buffer;
    while (1) {
        if (std::cin >> buffer) {
            if (buffer < floor) {
                std::cout << "Your input was too small! Try again: ";
            }
            else if (buffer > ceil) {
                std::cout << "Your input was too big! Try again: ";
            }
            else {
                return buffer;
            }
        }
        else {
            std::cout << "Invalid input! Please try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}