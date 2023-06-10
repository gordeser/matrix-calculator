//
// Created by gordeser on 15.05.2023.
//

#include "TrimmingOperation.h"
#include "../Exceptions/OperationException.h"

TrimmingOperation::TrimmingOperation(std::shared_ptr<Matrix> &lhs,
                                     size_t rows, size_t cols,
                                     size_t offsetRows, size_t offsetCols)
        : Operation(lhs), m_rows(rows), m_cols(cols),
          m_offsetRows(offsetRows), m_offsetCols(offsetCols) {}

std::vector <std::vector <double>> TrimmingOperation::execute() const {
    if (m_rows + m_offsetRows > m_lhs->numRows())
        throw OperationException("Number of rows and rows offset are too large ");

    if (m_cols + m_offsetCols > m_lhs->numCols())
        throw OperationException("Number of columns and columns offset are too large");

    std::vector <std::vector <double>> result(m_rows, std::vector<double>(m_cols, 0));
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            result[i][j] = m_lhs->getVal(i + m_offsetRows, j + m_offsetCols);

    return result;
}
