//
// Created by duama on 06.06.2023.
//

#include "ExporterException.h"

ExporterException::ExporterException(const std::string &message) : m_message(message) {}

const char *ExporterException::what() const noexcept {
    return m_message.c_str();
}
