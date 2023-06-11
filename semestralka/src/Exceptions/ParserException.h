//
// Created by duama on 06.06.2023.
//

#ifndef PA2_PARSEREXCEPTION_H
#define PA2_PARSEREXCEPTION_H


#include <exception>
#include <string>

class ParserException : public std::exception {
    /** @var description of error */
    std::string m_message;
public:
    /**
     * Constructor
     * @param message describes error
     */
    explicit ParserException(std::string message);
    /**
     * Method that returns text of error
     * @return c-string that contains text of error
     */
    const char *what() const noexcept override;
};


#endif //PA2_PARSEREXCEPTION_H
