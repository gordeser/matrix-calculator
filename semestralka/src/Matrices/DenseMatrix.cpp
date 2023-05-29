//
// Created by gordeser on 14.05.2023.
//

#include "DenseMatrix.h"

DenseMatrix::DenseMatrix(std::size_t numRows, std::size_t numCols) : Matrix(numRows, numCols) {}

double DenseMatrix::getVal(std::size_t row, std::size_t col) const {
    auto it = m_data.find(std::make_pair(row, col));
    if (it != m_data.end()) {
        return it->second;
    }
    // call exception
    return 0;
}

