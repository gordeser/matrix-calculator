//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_CONSOLE_H
#define PA2_CONSOLE_H

#include "UserInterface.h"


class ConsoleUI : public UserInterface {
public:
    void showText(const std::string &text) override;
    std::string getInput() override;
    void showGreeting() override;
    void showFarewall() override;
};

#endif //PA2_CONSOLE_H
