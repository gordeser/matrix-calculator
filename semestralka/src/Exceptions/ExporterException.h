//
// Created by duama on 06.06.2023.
//

#ifndef PA2_EXPORTEREXCEPTION_H
#define PA2_EXPORTEREXCEPTION_H


#include <exception>
#include <string>

class ExporterException : public std::exception {
    /** @var description of error */
    std::string m_message;
public:
    /**
     * Constructor
     * @param message describes error
     */
    ExporterException(const std::string &message);
    /**
     * Method that returns text of error
     * @return c-string that contains text of error
     */
    virtual const char *what() const noexcept override;
};


#endif //PA2_EXPORTEREXCEPTION_H
