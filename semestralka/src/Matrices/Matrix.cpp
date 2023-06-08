//
// Created by gordeser on 13.05.2023.
//

#include <vector>
#include <math.h>
#include "../Exception.h"
#include "../Operations/GaussEliminationOperation.h"
#include "Matrix.h"

Matrix::Matrix(std::size_t numRows, std::size_t numCols) : m_rows(numRows), m_cols(numCols) {}

std::size_t Matrix::numRows() const {
    return m_rows;
}

std::size_t Matrix::numCols() const {
    return m_cols;
}

std::size_t Matrix::rank() const {
    auto gemmedMatrix = std::make_shared<GaussEliminationOperation>(clone())->execute();
    size_t rank = 0;

    // rank = count of non-zero rows
    for (size_t i = 0; i < m_rows; ++i) {
        bool isZero = true;
        for (size_t j = 0; j < m_cols; ++j)
            if (gemmedMatrix[i][j] != 0)
                isZero = false;
        if (!isZero)
            rank++;
    }
    return rank;
}

double Matrix::determinant() const {
    if (numRows() != numCols())
        throw Exception("error");

    std::vector <std::vector <double>> matrix(numRows(), std::vector<double> (numCols()));
    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            matrix[i][j] = getVal(i, j);
        }
    }
    return countDeterminant(matrix, numRows());
}

// taken from https://www.tutorialspoint.com/cplusplus-program-to-compute-determinant-of-a-matrix
double Matrix::countDeterminant(std::vector<std::vector<double>> matrix, size_t size) const {
    if (m_rows != m_cols)
        throw Exception("error");

    if (size == 1) return matrix[0][0];
    if (size == 2) return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

    double result = 0;
    std::vector <std::vector <double>> submatrix(size, std::vector <double> (size));

    for (size_t x = 0; x < size; ++x) {
        size_t subi = 0;
        for (size_t i = 1; i < size; ++i) {
            size_t subj = 0;
            for (size_t j = 0; j < size; ++j) {
                if (j == x) continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        result += pow(-1, x) * matrix[0][x] * countDeterminant(submatrix, size - 1);
    }
    return result;
}

size_t Matrix::countMaxDigits(size_t column) const {
    size_t maxDigits = 0;
    auto matrix = clone();
    for (size_t i = 0; i < m_rows; ++i) {
        std::ostringstream ss;
        ss << getVal(i, column);
        maxDigits = std::max(maxDigits, ss.str().length());
    }
    return maxDigits;
}



