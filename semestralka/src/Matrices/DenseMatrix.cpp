//
// Created by gordeser on 14.05.2023.
//

#include <iomanip>
#include "DenseMatrix.h"

DenseMatrix::DenseMatrix(size_t numRows, size_t numCols, std::vector<std::vector <double>> data) : Matrix(numRows, numCols), m_data(data) {}

double DenseMatrix::getVal(size_t row, size_t col) const {
    return m_data[row][col];
}

std::shared_ptr<Matrix> DenseMatrix::clone() const {
    return std::make_shared<DenseMatrix>(*this);
}

std::string DenseMatrix::print(const std::string &matrixName) const {
    std::ostringstream result;
    result << (matrixName != "" ? "[" + matrixName + "] " : "");
    result << "Dense Matrix (" << m_rows << ":" << m_cols << ")\n";
    for (size_t i = 0; i < m_rows; ++i) {
        result << "| ";
        for (size_t j = 0; j < m_cols; ++j)
            result << std::setw(countMaxDigits(j)) << std::setfill(' ') << m_data[i][j] <<  " ";
        result << "|\n";
    }
    return result.str();
}

std::string DenseMatrix::printToFile(const std::string &matrixName) const {
    std::ostringstream result;
    result << matrixName << " D " << m_rows << " " << m_cols;
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            result << " " << m_data[i][j];
    return result.str();
}



