//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TRIMMINGOPERATION_H
#define PA2_TRIMMINGOPERATION_H

#include "Operation.h"

class TrimmingOperation : public Operation {
protected:
    /** @var count of rows of new matrix */
    size_t m_rows;
    /** @var count of columns of new matrix*/
    size_t m_cols;
    /** @var rows offset */
    size_t m_offsetRows;
    /** @var columns offset */
    size_t m_offsetCols;
public:
    /**
     * Constructor to set matrix, new count of rows and columns, rows and columns offsets
     * @param lhs matrix on left hand side
     * @param rows count of rows of new matrix
     * @param cols count of columns of new matrix
     * @param offsetRows
     * @param offsetCols
     */
    TrimmingOperation(std::shared_ptr<Matrix> &lhs, size_t rows, size_t cols, size_t offsetRows, size_t offsetCols);
    /**
     * Overridden method to execute trimming operation
     * @return values of matrix after operation
     * @throw OperationException if number of rows and rows offset are too large, or number of columns and columns offset
     */
    std::vector <std::vector <double>> execute() const;
};

#endif //PA2_TRIMMINGOPERATION_H
