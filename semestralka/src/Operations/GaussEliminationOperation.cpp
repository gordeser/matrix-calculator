//
// Created by gordeser on 15.05.2023.
//

#include "GaussEliminationOperation.h"

GaussEliminationOperation::GaussEliminationOperation(std::shared_ptr<Matrix> lhs) : Operation(std::move(lhs)) {}

void GaussEliminationOperation::reduceRowEchelon(std::vector<std::vector<double>> &matrix) const {
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
        Utilities::swapRows(matrix, i, row);

        // scale the pivot row so that the pivot element becomes 1
        Utilities::scaleRow(matrix, row, 1.0 / matrix[row][leadColumn]);

        // perform row operations to eliminate other elements in the column
        for (size_t j = 0; j < m_lhs->numRows(); ++j)
            if (j != row)
                // add a scaled pivot row to eliminate the element in the current row
                Utilities::addScaledRow(matrix, row, j, -matrix[j][leadColumn]);

        ++leadColumn;  // move to the next column
    }
}

std::vector<std::vector<double>> GaussEliminationOperation::execute() const {
    std::vector <std::vector <double>> result(m_lhs->numRows(), std::vector<double> (m_lhs->numCols(), 0));

    for (size_t i = 0; i < m_lhs->numRows(); ++i)
        for (size_t j = 0; j < m_lhs->numCols(); ++j)
            result[i][j] = m_lhs->getVal(i, j);

    reduceRowEchelon(result);
    return result;
}
