//
// Created by gordeser on 14.05.2023.
//

#include <vector>
#include "IdentityMatrix.h"

IdentityMatrix::IdentityMatrix(std::size_t numRows, std::size_t numCols) : Matrix(numRows, numCols) {}

double IdentityMatrix::getVal(std::size_t row, std::size_t col) const {
    if (row == col)
        return 1;
    return 0;
}

std::size_t IdentityMatrix::rank() const {
    return m_rows;
}
