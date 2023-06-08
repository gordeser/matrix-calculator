//
// Created by duama on 08.06.2023.
//

#include "MatrixException.h"

MatrixException::MatrixException(const std::string &message) : m_message(message) {}

const char *MatrixException::what() const noexcept {
    return m_message.c_str();
}
