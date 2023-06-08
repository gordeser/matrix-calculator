//
// Created by gordeser on 15.05.2023.
//

#include "GaussEliminationOperation.h"

GaussEliminationOperation::GaussEliminationOperation(const std::shared_ptr<Matrix> &lhs) : Operation(lhs) {}

void GaussEliminationOperation::swapRows(std::vector<std::vector<double>> &matrix, size_t firstRow, size_t secondRow) {
    if (firstRow != secondRow)
        std::swap(matrix[firstRow], matrix[secondRow]);
}

void GaussEliminationOperation::scaleRow(std::vector<std::vector<double>> &matrix, size_t row, double number) {
    for (double &value : matrix[row])
        value *= number;
}

void GaussEliminationOperation::addScaledRow(std::vector<std::vector<double>> &matrix, size_t sourceRow, size_t targetRow, double number) {
    for (size_t i = 0; i < matrix[targetRow].size(); ++i)
        matrix[targetRow][i] += number * matrix[sourceRow][i];
}

void GaussEliminationOperation::reduceRowEchelon(std::vector<std::vector<double>> &matrix) {
    size_t leadColumn = 0;
    for (size_t row = 0; row < m_lhs->numRows(); ++row) {
        if (leadColumn >= m_lhs->numCols())
            return;  // all columns are processed

        size_t i = row;
        while (matrix[i][leadColumn] == 0) { // find a non-zero pivot element in the column
            ++i;
            if (i == m_lhs->numRows()) { // if no non-zero pivot element found in the column
                i = row;
                ++leadColumn;
                if (leadColumn == m_lhs->numCols())
                    return;  // all columns are processed
            }
        }

        // swap the current row with the row containing the pivot element
        swapRows(matrix, i, row);

        // scale the pivot row so that the pivot element becomes 1
        scaleRow(matrix, row, 1.0 / matrix[row][leadColumn]);

        // perform row operations to eliminate other elements in the column
        for (size_t j = 0; j < m_lhs->numRows(); ++j)
            if (j != row)
                // add a scaled pivot row to eliminate the element in the current row
                addScaledRow(matrix, row, j, -matrix[j][leadColumn]);

        ++leadColumn;  // move to the next column
    }
}

std::vector<std::vector<double>> GaussEliminationOperation::execute() {
    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector<double> (m_lhs->numCols(), 0));

    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(i, j);

    reduceRowEchelon(result);
    return result;
}
