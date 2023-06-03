//
// Created by gordeser on 14.05.2023.
//

#include "DenseMatrix.h"

DenseMatrix::DenseMatrix(std::size_t numRows, std::size_t numCols, std::vector<std::vector <double>> data) : Matrix(numRows, numCols), m_data(data) {}

double DenseMatrix::getVal(std::size_t row, std::size_t col) const {
    return m_data[row][col];
}

void DenseMatrix::setVal(std::size_t row, std::size_t col, double val) {
    // todo add check
    m_data[std::make_pair(row, col)] = val;
}



