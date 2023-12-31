//
// Created by gordeser on 14.05.2023.
//

#include <iomanip>
#include "SparseMatrix.h"
#include "../Exceptions/MatrixException.h"

SparseMatrix::SparseMatrix(size_t numRows, size_t numCols, std::map <std::pair<size_t, size_t>, double> data) : Matrix(numRows, numCols), m_data(std::move(data)) {}

double SparseMatrix::getVal(size_t row, size_t col) const {
    if (row >= numRows())
        throw MatrixException("Row must be less than numRows of matrix");
    if (col >= numCols())
        throw MatrixException("Column must be less than numCols of matrix");

    // if there is row col in data, then it has some value
    if (m_data.find(std::make_pair(row, col)) != m_data.end())
        return m_data.at(std::make_pair(row, col));
    // else 0
    return 0;
}

std::shared_ptr<Matrix> SparseMatrix::clone() const {
    return std::make_shared<SparseMatrix>(*this);
}

std::string SparseMatrix::print(const std::string &matrixName) const {
    std::ostringstream result;
    result << (!matrixName.empty() ? "[" + matrixName + "] " : "");
    result << "Sparse Matrix (" << m_rows << ":" << m_cols << ")\n";
    for (size_t i = 0; i < m_rows; ++i) {
        result << "| ";
        for (size_t j = 0; j < m_cols; ++j) {
            if (m_data.find(std::make_pair(i, j)) != m_data.end())
                result << std::setw(countMaxDigits(j)) << std::setfill(' ') << m_data.at(std::make_pair(i, j)) << " ";
            else
                result << std::setw(countMaxDigits(j)) << std::setfill(' ') << "0 ";
        }
        result << "|\n";
    }
    return result.str();
}

std::string SparseMatrix::printToFile(const std::string &matrixName) const {
    std::ostringstream result;
    result << matrixName + " S " << m_rows << " " << m_cols ;
    for (const auto &elem : m_data)
        result << " " << elem.first.first << " " << elem.first.second << " " << elem.second;
    return result.str();
}
