//
// Created by duama on 05.06.2023.
//

#include "MultiplicationNumberOperation.h"

MultiplicationNumberOperation::MultiplicationNumberOperation(std::shared_ptr<Matrix> lhs, double rhs) : Operation(std::move(lhs)), m_rhs(rhs) {}

std::vector<std::vector<double>> MultiplicationNumberOperation::execute() const {
    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector<double> (m_lhs->numCols(), 0));
    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(i, j) * m_rhs;

    return result;
}


