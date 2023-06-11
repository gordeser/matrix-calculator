//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_DENSEMATRIX_H
#define PA2_DENSEMATRIX_H

#include "Matrix.h"

class DenseMatrix : public Matrix {
    /** @var contains values of matrix */
    std::vector<std::vector <double>> m_data;
public:
    /**
     * Constructor to set count of rows, count of columns and values of matrix
     * @param numRows count of rows
     * @param numCols count of columns
     * @param data values of matrix
     */
    DenseMatrix(size_t numRows, size_t numCols, std::vector<std::vector <double>> data);
    /**
     * Overridden method to get some value of matrix
     * @param row of value
     * @param col of value
     * @return value of matrix
     * @throw MatrixException if row or col is bigger than numRows or numCols
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

#endif //PA2_DENSEMATRIX_H
