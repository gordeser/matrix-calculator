//
// Created by gordeser on 14.05.2023.
//

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(size_t numRows, size_t numCols, std::map <std::pair<size_t, size_t>, double> data) : Matrix(numRows, numCols), m_data(data) {}

double SparseMatrix::getVal(size_t row, size_t col) const {
    if (m_data.find(std::make_pair(row, col)) != m_data.end())
        return m_data.at(std::make_pair(row, col));
    return 0;
}

std::shared_ptr<Matrix> SparseMatrix::clone() const {
    return std::make_shared<SparseMatrix>(*this);
}
