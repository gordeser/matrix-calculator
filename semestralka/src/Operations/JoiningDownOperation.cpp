//
// Created by gordeser on 15.05.2023.
//

#include "JoiningDownOperation.h"
#include "../Exceptions/OperationException.h"

JoiningDownOperation::JoiningDownOperation(const std::shared_ptr<Matrix> &lhs, const std::shared_ptr<Matrix> &rhs) : BinaryOperation(lhs, rhs) {}

std::vector<std::vector<double>> JoiningDownOperation::execute() const {
    if (m_lhs->numCols() != m_rhs->numCols())
        throw OperationException("Number of columns must be equal");

    std::vector <std::vector <double>> result(m_lhs->numRows()+m_rhs->numRows(), std::vector<double> (m_lhs->numCols(), 0));
    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(i, j);

    for (size_t i = 0; i < m_rhs->numRows(); ++i)
        for (size_t j = 0; j < m_rhs->numCols(); ++j)
            result[i + m_lhs->numRows()][j] = m_rhs->getVal(i, j);

    return result;
}
