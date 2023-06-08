//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_DENSEMATRIX_H
#define PA2_DENSEMATRIX_H

#include "Matrix.h"

class DenseMatrix : public Matrix {
    std::vector<std::vector <double>> m_data;
public:
    DenseMatrix(std::size_t numRows, std::size_t numCols, std::vector<std::vector <double>> data);
    double getVal(std::size_t row, std::size_t col) const override;
    std::shared_ptr<Matrix> clone() const override;
    std::string print(const std::string &matrixName) const override;
    std::string printToFile(const std::string &matrixName) const override;
};

#endif //PA2_DENSEMATRIX_H
