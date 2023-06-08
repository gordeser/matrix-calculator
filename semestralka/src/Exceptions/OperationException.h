//
// Created by duama on 07.06.2023.
//

#ifndef PA2_OPERATIONEXCEPTION_H
#define PA2_OPERATIONEXCEPTION_H

#include <exception>
#include <string>


class OperationException : public std::exception {
    std::string m_message;
public:
    OperationException(const std::string &message);
    virtual const char *what() const noexcept override;
};


#endif //PA2_OPERATIONEXCEPTION_H
