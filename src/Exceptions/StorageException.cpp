//
// Created by duama on 06.06.2023.
//

#include "StorageException.h"

StorageException::StorageException(std::string message) : m_message(std::move(message)) {}

const char *StorageException::what() const noexcept {
    return m_message.c_str();
}
