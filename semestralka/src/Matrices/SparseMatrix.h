//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_SPARSEMATRIX_H
#define PA2_SPARSEMATRIX_H

#include "Matrix.h"
#include <vector>
#include <map>

class SparseMatrix : public Matrix {
    std::map <std::pair<std::size_t, std::size_t>, double> m_data;
public:
    SparseMatrix(std::size_t numRows, std::size_t numCols);
    double getVal(std::size_t row, std::size_t col) const override;
    std::shared_ptr<Matrix> clone() const override;
    void print() const override;
    void printToFile() const override;
};

#endif //PA2_SPARSEMATRIX_H
