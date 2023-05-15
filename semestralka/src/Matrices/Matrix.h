//
// Created by gordeser on 11.05.2023.
//


#include <cstdlib>
#include <memory>

class Matrix {
protected:
    std::size_t m_rows;
    std::size_t m_cols;
public:
    Matrix(std::size_t numRows, std::size_t numCols);
    virtual ~Matrix() {}
    std::size_t numRows() const;
    std::size_t numCols() const;
    virtual double getVal(std::size_t row, std::size_t col) const = 0;
    virtual void setVal(std::size_t row, std::size_t col, double val) = 0;
    virtual std::size_t rank() const = 0;
    virtual double determinant() const = 0;
    virtual std::shared_ptr<Matrix> clone() const = 0;
    virtual void print() const = 0;
    virtual void printToFile() const = 0;
};