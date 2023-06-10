//
// Created by gordeser on 15.05.2023.
//

#include "AdditionOperation.h"
#include "../Exceptions/OperationException.h"

AdditionOperation::AdditionOperation(const std::shared_ptr<Matrix> &lhs, const std::shared_ptr<Matrix> &rhs) : BinaryOperation(lhs, rhs) {}

std::vector <std::vector <double>> AdditionOperation::execute() const {
    if (m_lhs->numRows() != m_rhs->numRows())
        throw OperationException("Number of rows must be equal\n");

    if (m_lhs->numCols() != m_rhs->numCols())
        throw OperationException("Number of columns must be equal\n");

    std::vector <std::vector <double>> result (m_lhs->numRows(), std::vector <double> (m_lhs->numCols(), 0));
    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(i, j) + m_rhs->getVal(i, j);
    return result;
}
