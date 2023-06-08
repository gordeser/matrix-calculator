//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_MATRIXCALCULATOR_H
#define PA2_MATRIXCALCULATOR_H

#include "Parser.h"
#include "UserInterfaces/Console.h"

class MatrixCalculator {
    Parser m_parser;
    ConsoleUI m_console;

    void showGreeting();
    void showFarewall();
public:
    void runApplication();
};

#endif //PA2_MATRIXCALCULATOR_H
