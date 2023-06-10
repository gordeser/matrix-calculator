//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_SPARSEMATRIX_H
#define PA2_SPARSEMATRIX_H

#include "Matrix.h"
#include <map>

class SparseMatrix : public Matrix {
    /** @var contains values of matrix in map, where key is pair of row and column of value, value is value of matrix */
    std::map <std::pair<size_t, size_t>, double> m_data;
public:
    /**
     * Constructor to set count of rows, count of columns and values of matrix
     * @param numRows count of rows
     * @param numCols count of columns
     * @param data values of matrix
     */
    SparseMatrix(size_t numRows, size_t numCols, std::map <std::pair<size_t, size_t>, double> data);
    /**
     * Overridden method to get some value of matrix
     * @param row of value
     * @param col of value
     * @return value of matrix
     */
    double getVal(size_t row, size_t col) const override;
    /**
     * Overridden method to make deep copy of matrix
     * @return shared smart-pointer on matrix copy
     */
    std::shared_ptr<Matrix> clone() const override;
    /**
     * Overridden method to get information about matrix
     * @param matrixName information to get
     * @return string that contains information about matrix
     */
    std::string print(const std::string &matrixName) const override;
    /**
     * Overridden method to get information about matrix to export it in file
     * @param matrixName information to get
     * @return string that contains information about matrix in handy way
     */
    std::string printToFile(const std::string &matrixName) const override;
};

#endif //PA2_SPARSEMATRIX_H
