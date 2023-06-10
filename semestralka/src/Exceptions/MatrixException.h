//
// Created by duama on 08.06.2023.
//

#ifndef PA2_MATRIXEXCEPTION_H
#define PA2_MATRIXEXCEPTION_H


#include <exception>
#include <string>

class MatrixException : public std::exception {
    /** @var description of error */
    std::string m_message;
public:
    /**
     * Constructor
     * @param message describes error
     */
    MatrixException(const std::string &message);
    /**
     * Method that returns text of error
     * @return c-string that contains text of error
     */
    virtual const char *what() const noexcept override;
};


#endif //PA2_MATRIXEXCEPTION_H
