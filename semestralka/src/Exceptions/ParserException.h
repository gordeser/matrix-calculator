//
// Created by duama on 06.06.2023.
//

#ifndef PA2_PARSEREXCEPTION_H
#define PA2_PARSEREXCEPTION_H


#include <exception>
#include <string>

class ParserException : public std::exception {
    std::string m_message;
public:
    ParserException(const std::string &message);
    virtual const char *what() const noexcept override;
};


#endif //PA2_PARSEREXCEPTION_H
