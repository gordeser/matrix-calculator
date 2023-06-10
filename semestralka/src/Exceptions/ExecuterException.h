//
// Created by duama on 10.06.2023.
//

#ifndef PA2_EXECUTEREXCEPTION_H
#define PA2_EXECUTEREXCEPTION_H


#include <exception>
#include <string>

class ExecuterException : public std::exception {
    /** @var description of error */
    std::string m_message;
public:
    /**
     * Constructor
     * @param message describes error
     */
    ExecuterException(const std::string &message);
    /**
     * Method that returns text of error
     * @return c-string that contains text of error
     */
    virtual const char *what() const noexcept override;
};


#endif //PA2_EXECUTEREXCEPTION_H
