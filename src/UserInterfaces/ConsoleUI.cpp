//
// Created by gordeser on 15.05.2023.
//

#include <iostream>
#include <algorithm>
#include "ConsoleUI.h"

void ConsoleUI::showText(const std::string &text) const {
    std::cout << text;
}

std::string ConsoleUI::getInput() const {
    std::string input;
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    if (std::cin.eof())
        return "quit";
    return input;
}