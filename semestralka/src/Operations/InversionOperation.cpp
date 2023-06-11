//
// Created by gordeser on 15.05.2023.
//

#include "InversionOperation.h"
#include "../Exceptions/OperationException.h"
#include "JoiningRightOperation.h"
#include "TrimmingOperation.h"

InversionOperation::InversionOperation(std::shared_ptr<Matrix> lhs) : Operation(std::move(lhs)) {}

void InversionOperation::inverse(std::vector<std::vector<double>> &matrix) const {
    // apply GEM to convert A matrix in [A | I] to reduced row echelon form
    for (size_t row = 0; row < m_lhs->numRows(); ++row) {
        size_t pivotRow = row;

        // find a non-zero pivot element in the column
        while (pivotRow < m_lhs->numRows() && matrix[pivotRow][row] == 0)
            pivotRow++;

        // no non-zero pivot element found => matrix is singular
        if (pivotRow == m_lhs->numRows())
            throw OperationException("Matrix is singular, inverse matrix does not exist\n");

        Utilities::swapRows(matrix, row, pivotRow);
        Utilities::scaleRow(matrix, row, 1.0 / matrix[row][row]);

        for (size_t i = 0; i < m_lhs->numRows(); ++i)
            if (i != row)
                Utilities::addScaledRow(matrix, row, i, -matrix[i][row]);
    }
}

std::vector<std::vector<double>> InversionOperation::execute() const {
    if (m_lhs->numRows() != m_lhs->numCols())
        throw OperationException("Matrix must be square\n");

    if (m_lhs->determinant() == 0)
        throw OperationException("Matrix determinant must be non-zero\n");

    // create matrix [A | I]
    auto IMatrix = std::make_shared<IdentityMatrix>(m_lhs->numRows(), m_lhs->numCols());
    std::vector <std::vector <double>> extended = JoiningRightOperation(m_lhs, IMatrix).execute();

    // [A | I] -> [I | A^-1]
    inverse(extended);

    // trim I matrix from [I | A^-1]
    auto inversed = Utilities::createMatrix(extended);
    auto result = std::make_shared<TrimmingOperation>(inversed,  m_lhs->numRows(), m_lhs->numCols(), 0, m_lhs->numCols())->execute();

    return result;
}
