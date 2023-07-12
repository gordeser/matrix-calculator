//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_IDENTITYMATRIX_H
#define PA2_IDENTITYMATRIX_H

#include "Matrix.h"

class IdentityMatrix : public Matrix {
public:
    /**
     * Constructor to set count of rows, count of columns
     * @param numRows count of rows
     * @param numCols count of columns
     */
    IdentityMatrix(size_t numRows, size_t numCols);
    /**
     * Overridden method to get some value of matrix
     * @param row of value
     * @param col of value
     * @return value of matrix
     */
    double getVal(size_t row, size_t col) const override;
    /**
     * Overridden method to count rank of matrix
     * @return rank of matrix
     */
    size_t rank() const override;
    /**
     * Overridden method to count determinant of matrix
     * @return determinant of matrix
     */
    double determinant() const override;
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

#endif //PA2_IDENTITYMATRIX_H
