//
// Created by gordeser on 15.05.2023.
//

#include <iostream>
#include "Console.h"

void ConsoleUI::showText(const std::string &text) {
    std::cout << text;
}

void ConsoleUI::showGreeting() {
    showText("Hello!\n");
    showText("Available commands you can get with input HELP'\n");
    showText("Your input: ");
}

void ConsoleUI::showFarewall() {
    showText("Goodbye!\n");
}
