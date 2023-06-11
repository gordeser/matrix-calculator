//
// Created by gordeser on 15.05.2023.
//

#include "MultiplicationOperation.h"
#include "../Exceptions/OperationException.h"

MultiplicationOperation::MultiplicationOperation(const std::shared_ptr<Matrix> &lhs, const std::shared_ptr<Matrix> &rhs) : BinaryOperation(lhs, rhs) {}

std::vector <std::vector <double>> MultiplicationOperation::execute() const {
    if (m_lhs->numCols() != m_rhs->numRows())
        throw OperationException("Number of first matrix columns must be equal to number of second matrix rows\n");

    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector <double> (m_rhs->numCols(), 0));

    for (size_t i = 0; i < m_lhs->numRows(); ++i) {
        for (size_t j = 0; j < m_rhs->numCols(); ++j) {
            double sum = 0;
            for (size_t k = 0; k < m_lhs->numCols(); ++k) // count sums of columns
                sum += m_lhs->getVal(i, k) * m_rhs->getVal(k, j);
            result[i][j] = sum;
        }
    }
    return result;
}
