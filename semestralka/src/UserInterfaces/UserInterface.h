//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_USERINTERFACE_H
#define PA2_USERINTERFACE_H

#include <string>

class UserInterface {
public:
    virtual ~UserInterface() {}
    virtual void showText(const std::string &text) = 0;
    virtual std::string getInput() = 0;
};

#endif //PA2_USERINTERFACE_H
