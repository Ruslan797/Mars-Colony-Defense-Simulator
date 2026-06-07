#include "InputSystem.h"

#include <iostream>
#include <string>

bool InputSystem::shouldQuit() const
{
    std::cout << "Press Enter to continue or q to quit: ";

    std::string input;

    std::getline(std::cin, input);

    return input == "q" || input == "Q";
}