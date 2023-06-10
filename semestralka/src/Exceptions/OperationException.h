//
// Created by duama on 07.06.2023.
//

#ifndef PA2_OPERATIONEXCEPTION_H
#define PA2_OPERATIONEXCEPTION_H

#include <exception>
#include <string>

class OperationException : public std::exception {
    /** @var description of error */
    std::string m_message;
public:
    /**
     * Constructor
     * @param message describes error
     */
    OperationException(const std::string &message);
    /**
     * Method that returns text of error
     * @return c-string that contains text of error
     */
    virtual const char *what() const noexcept override;
};


#endif //PA2_OPERATIONEXCEPTION_H
