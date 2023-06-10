//
// Created by duama on 06.06.2023.
//

#ifndef PA2_STORAGEEXCEPTION_H
#define PA2_STORAGEEXCEPTION_H


#include <exception>
#include <string>

/** @class inherited from std::exception to handle all exceptions in storage section */
class StorageException : public std::exception {
    /** @var description of error */
    std::string m_message;
public:
    /**
     * Constructor
     * @param message describes error
     */
    StorageException(const std::string &message);
    /**
     * Method that returns text of error
     * @return c-string that contains text of error
     */
    virtual const char *what() const noexcept override;
};


#endif //PA2_STORAGEEXCEPTION_H
