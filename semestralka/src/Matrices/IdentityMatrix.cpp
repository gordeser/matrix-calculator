//
// Created by gordeser on 14.05.2023.
//

#include "IdentityMatrix.h"

IdentityMatrix::IdentityMatrix(size_t numRows, size_t numCols) : Matrix(numRows, numCols) {}

double IdentityMatrix::getVal(size_t row, size_t col) const {
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

std::string IdentityMatrix::print(const std::string &matrixName) const {
    std::ostringstream result;
    result << (matrixName != "" ? "[" + matrixName + "] " : "");
    result << "Identity Matrix (" << m_rows << ":" << m_cols << ")\n";
    for (size_t i = 0; i < m_rows; ++i) {
        result << "| ";
        for (size_t j = 0; j < m_cols; ++j) {
            if (i == j) result << "1 ";
            else result << "0 ";
        }
        result << "|\n";
    }
    return result.str();
}

std::string IdentityMatrix::printToFile(const std::string &matrixName) const {
    std::ostringstream result;
    result << matrixName << " I " << m_rows;
    return result.str();
}
