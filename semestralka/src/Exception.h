//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXCEPTION_H
#define PA2_EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception {
    std::string m_message;
public:
    Exception(const std::string &message);
    virtual const char *what() const noexcept override;
};

#endif //PA2_EXCEPTION_H
