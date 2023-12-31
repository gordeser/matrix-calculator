//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_USERINTERFACE_H
#define PA2_USERINTERFACE_H

#include <string>

class UserInterface {
public:
    /** Virtual destructor */
    virtual ~UserInterface() = default;
    /**
     * Virtual method to show text
     * @param text to show
     */
    virtual void showText(const std::string &text) const = 0;
    /**
     * Virtual method to get input from user
     * @return string input
     */
    virtual std::string getInput() const = 0;
};

#endif //PA2_USERINTERFACE_H
