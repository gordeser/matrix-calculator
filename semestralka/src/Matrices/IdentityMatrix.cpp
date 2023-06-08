//
// Created by gordeser on 14.05.2023.
//

#include "IdentityMatrix.h"

IdentityMatrix::IdentityMatrix(std::size_t numRows, std::size_t numCols) : Matrix(numRows, numCols) {}

double IdentityMatrix::getVal(std::size_t row, std::size_t col) const {
    return (row == col) ? 1 : 0;
}

std::size_t IdentityMatrix::rank() const {
    return m_rows;
}

double IdentityMatrix::determinant() const {
    return 1;
}

std::shared_ptr<Matrix> IdentityMatrix::clone() const {
    return std::make_shared<IdentityMatrix>(*this);
}
