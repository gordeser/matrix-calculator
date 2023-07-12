//
// Created by duama on 05.06.2023.
//

#include "Operation.h"

Operation::Operation(std::shared_ptr<Matrix> lhs) : m_lhs(std::move(lhs)) {}
