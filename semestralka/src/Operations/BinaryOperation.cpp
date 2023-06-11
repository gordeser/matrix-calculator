//
// Created by duama on 05.06.2023.
//

#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(std::shared_ptr<Matrix> lhs, std::shared_ptr<Matrix> rhs) : Operation(std::move(lhs)), m_rhs(std::move(rhs)) {}
