//
// Created by gordeser on 13.05.2023.
//

#include "Matrix.h"

Matrix::Matrix(std::size_t numRows, std::size_t numCols) : m_rows(numRows), m_cols(numCols) {}

std::size_t Matrix::numRows() const {
    return m_rows;
}

std::size_t Matrix::numCols() const {
    return m_cols;
}


