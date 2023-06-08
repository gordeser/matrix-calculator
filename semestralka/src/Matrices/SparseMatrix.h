//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_SPARSEMATRIX_H
#define PA2_SPARSEMATRIX_H

#include "Matrix.h"
#include <map>

class SparseMatrix : public Matrix {
    std::map <std::pair<size_t, size_t>, double> m_data;
public:
    SparseMatrix(size_t numRows, size_t numCols, std::map <std::pair<size_t, size_t>, double> data);
    double getVal(size_t row, size_t col) const override;
    std::shared_ptr<Matrix> clone() const override;
    std::string print(const std::string &matrixName) const override;
    std::string printToFile(const std::string &matrixName) const override;
};

#endif //PA2_SPARSEMATRIX_H
