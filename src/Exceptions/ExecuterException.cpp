//
// Created by duama on 10.06.2023.
//

#include "ExecuterException.h"

ExecuterException::ExecuterException(std::string message) : m_message(std::move(message)) { }

const char *ExecuterException::what() const noexcept {
    return m_message.c_str();
}
