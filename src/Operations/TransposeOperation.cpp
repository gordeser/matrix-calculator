//
// Created by gordeser on 15.05.2023.
//

#include "TransposeOperation.h"

TransposeOperation::TransposeOperation(std::shared_ptr<Matrix> lhs) : Operation(std::move(lhs)) {}

std::vector <std::vector <double>> TransposeOperation::execute() const {
    std::vector <std::vector <double>> result(m_lhs->numCols(), std::vector<double> (m_lhs->numRows(), 0));
    for (size_t i = 0; i < m_lhs->numCols(); ++i)
        for (size_t j = 0; j < m_lhs->numRows(); ++j)
            result[i][j] = m_lhs->getVal(j, i);

    return result;
}
