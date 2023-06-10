//
// Created by gordeser on 15.05.2023.
//

#include "TransposeOperation.h"

TransposeOperation::TransposeOperation(std::shared_ptr<Matrix> lhs) : Operation(lhs) {}

std::vector <std::vector <double>> TransposeOperation::execute() const {
    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector<double> (m_lhs->numCols(), 0));
    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(j, i);

    return result;
}
