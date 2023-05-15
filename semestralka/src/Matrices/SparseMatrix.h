//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_SPARSEMATRIX_H
#define PA2_SPARSEMATRIX_H

#include "Matrix.h"
#include <vector>

class SparseMatrix : public Matrix {
    std::vector <std::vector <double>> m_data;
public:
    SparseMatrix(std::size_t numRows, std::size_t numCols);
    double getVal(std::size_t row, std::size_t col) const override;
    void setVal(std::size_t row, std::size_t col, double val) override;
    std::size_t rank() const override;
    double determinant() const override;
    std::shared_ptr<Matrix> clone() const override;
    void print() const override;
    void printToFile() const override;
};

#endif //PA2_SPARSEMATRIX_H
