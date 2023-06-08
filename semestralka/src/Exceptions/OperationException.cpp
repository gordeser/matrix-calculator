//
// Created by duama on 07.06.2023.
//

#include "OperationException.h"

OperationException::OperationException(const std::string &message) : m_message(message) {}

const char *OperationException::what() const noexcept {
    return m_message.c_str();
}


