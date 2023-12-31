//
// Created by gordeser on 15.05.2023.
//

#include "ExponentiationOperation.h"
#include "MultiplicationOperation.h"
#include "../Exceptions/OperationException.h"

ExponentiationOperation::ExponentiationOperation(std::shared_ptr<Matrix> lhs, int rhs): Operation(std::move(lhs)), m_rhs(rhs) {}

std::vector <std::vector <double>> ExponentiationOperation::execute() const {
    if (m_lhs->numRows() != m_lhs->numCols())
        throw OperationException("Matrix must be square\n");

    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector <double> (m_lhs->numCols(), 0));
    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        result[i][i] = 1;

    for (int i = 0; i < m_rhs; ++i) // multiply identity matrix by lhs rhs times
        result = MultiplicationOperation(Utilities::createMatrix(result), m_lhs->clone()).execute();
    return result;
}
