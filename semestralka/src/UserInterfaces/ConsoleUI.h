//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_CONSOLEUI_H
#define PA2_CONSOLEUI_H

#include "UserInterface.h"


/** @class inherits from class UserInterface to represent console user interface */
class ConsoleUI : public UserInterface {
public:
    /**
     * Overridden method to show text in console
     * @param text to show
     */
    void showText(const std::string &text) const override;
    /**
     * Overridden method to get input from user
     * @return string input
     */
    std::string getInput() const override;
};

#endif //PA2_CONSOLEUI_H
