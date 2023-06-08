//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_CONSOLEUI_H
#define PA2_CONSOLEUI_H

#include "UserInterface.h"


class ConsoleUI : public UserInterface {
public:
    void showText(const std::string &text) const override;
    std::string getInput() override;
};

#endif //PA2_CONSOLEUI_H
