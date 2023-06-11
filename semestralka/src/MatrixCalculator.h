//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_MATRIXCALCULATOR_H
#define PA2_MATRIXCALCULATOR_H

#include "Parser.h"
#include "UserInterfaces/ConsoleUI.h"

class MatrixCalculator {
    /** @var parcer for parcing user input */
    Parser m_parser;
    /** @var use console user-interface */
    ConsoleUI m_console;
    /** Method to show greeting message */
    void showGreeting() const;
    /** Method to show farewall message */
    void showFarewall() const;
public:
    /** Method to start the application */
    void runApplication();
};

#endif //PA2_MATRIXCALCULATOR_H
