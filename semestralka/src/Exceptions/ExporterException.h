//
// Created by duama on 06.06.2023.
//

#ifndef PA2_EXPORTEREXCEPTION_H
#define PA2_EXPORTEREXCEPTION_H


#include <exception>
#include <string>

class ExporterException : public std::exception {
    std::string m_message;
public:
    ExporterException(const std::string &message);
    virtual const char *what() const noexcept override;
};


#endif //PA2_EXPORTEREXCEPTION_H
