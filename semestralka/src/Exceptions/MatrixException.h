//
// Created by duama on 08.06.2023.
//

#ifndef PA2_MATRIXEXCEPTION_H
#define PA2_MATRIXEXCEPTION_H


#include <exception>
#include <string>

class MatrixException : public std::exception {
    std::string m_message;
public:
    MatrixException(const std::string &message);
    virtual const char *what() const noexcept override;
};


#endif //PA2_MATRIXEXCEPTION_H
