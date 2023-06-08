//
// Created by duama on 06.06.2023.
//

#include "ParserException.h"

ParserException::ParserException(const std::string &message) : m_message(message) {}

const char *ParserException::what() const noexcept {
    return m_message.c_str();
}
