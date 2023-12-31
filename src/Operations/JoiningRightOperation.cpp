//
// Created by gordeser on 15.05.2023.
//

#include "JoiningRightOperation.h"
#include "../Exceptions/OperationException.h"

JoiningRightOperation::JoiningRightOperation(std::shared_ptr<Matrix> lhs, std::shared_ptr<Matrix> rhs) : BinaryOperation(std::move(lhs), std::move(rhs)) {}

std::vector<std::vector<double>> JoiningRightOperation::execute() const {
    if (m_lhs->numRows() != m_rhs->numRows())
        throw OperationException("Number of rows must be equal");

    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector<double> (m_lhs->numCols() + m_rhs->numCols(), 0));

    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(i, j);

    for (size_t i = 0; i < m_rhs->numRows(); ++i)
        for (size_t j = 0; j < m_rhs->numCols(); ++j)
            result[i][j + m_lhs->numCols()] = m_rhs->getVal(i, j);

    return result;
}
