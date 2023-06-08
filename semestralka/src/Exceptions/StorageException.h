//
// Created by duama on 06.06.2023.
//

#ifndef PA2_STORAGEEXCEPTION_H
#define PA2_STORAGEEXCEPTION_H


#include <exception>
#include <string>

class StorageException : public std::exception {
    std::string m_message;
public:
    StorageException(const std::string &message);
    virtual const char *what() const noexcept override;
};


#endif //PA2_STORAGEEXCEPTION_H
