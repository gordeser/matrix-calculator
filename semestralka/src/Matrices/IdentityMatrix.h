//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_IDENTITYMATRIX_H
#define PA2_IDENTITYMATRIX_H

#include "Matrix.h"

class IdentityMatrix : public Matrix {
public:
    IdentityMatrix(size_t numRows, size_t numCols);
    double getVal(size_t row, size_t col) const override;
    size_t rank() const override;
    double determinant() const override;
    std::shared_ptr<Matrix> clone() const override;
    std::string print(const std::string &matrixName) const override;
    std::string printToFile(const std::string &matrixName) const override;
};

#endif //PA2_IDENTITYMATRIX_H
