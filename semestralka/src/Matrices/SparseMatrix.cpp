//
// Created by gordeser on 14.05.2023.
//

#include <stdexcept>
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(std::size_t numRows, std::size_t numCols) : Matrix(numRows, numCols) {}

double SparseMatrix::getVal(std::size_t row, std::size_t col) const {
    try {
        return m_data.at(std::make_pair(row, col));
    } catch(std::out_of_range &e) {
        return 0;
    }
}

std::shared_ptr<Matrix> SparseMatrix::clone() const {
    return std::make_shared<SparseMatrix>(*this);
}
