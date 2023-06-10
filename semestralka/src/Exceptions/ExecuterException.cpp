//
// Created by duama on 10.06.2023.
//

#include "ExecuterException.h"

ExecuterException::ExecuterException(const std::string &message) : m_message(message) { }

const char *ExecuterException::what() const noexcept {
    return m_message.c_str();
}
