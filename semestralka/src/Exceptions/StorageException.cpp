//
// Created by duama on 06.06.2023.
//

#include "StorageException.h"

StorageException::StorageException(const std::string &message) : m_message(message) {}

const char *StorageException::what() const noexcept {
    return m_message.c_str();
}
