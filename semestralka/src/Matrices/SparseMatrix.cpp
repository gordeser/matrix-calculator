//
// Created by gordeser on 14.05.2023.
//

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(std::size_t numRows, std::size_t numCols) : Matrix(numRows, numCols) {}

double SparseMatrix::getVal(std::size_t row, std::size_t col) const {
    // todo handle exception
    return m_data.at(std::make_pair(row, col));
}
