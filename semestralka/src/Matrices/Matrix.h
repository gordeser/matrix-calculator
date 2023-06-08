//
// Created by gordeser on 11.05.2023.
//

#ifndef PA2_MATRIX_H
#define PA2_MATRIX_H

#include <cstdlib>
#include <sstream>
#include <vector>
#include <math.h>
#include <vector>
#include <memory>

class Matrix {
    double countDeterminant(std::vector <std::vector <double>> matrix, size_t size) const;
protected:
    size_t m_rows;
    size_t m_cols;
    size_t countMaxDigits(size_t column) const;
public:
    Matrix(size_t numRows, size_t numCols);
    virtual ~Matrix() {}
    size_t numRows() const;
    size_t numCols() const;
    virtual size_t rank() const;
    virtual double determinant() const;
    virtual double getVal(size_t row, size_t col) const = 0;
    virtual std::shared_ptr<Matrix> clone() const = 0;
    virtual std::string print(const std::string &matrixName) const = 0;
    virtual std::string printToFile(const std::string &matrixName) const = 0;
};

#endif //PA2_MATRIX_H