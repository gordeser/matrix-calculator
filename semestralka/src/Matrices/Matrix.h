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
    /**
     * Method to count determinant of matrix
     * @param matrix in what count determinant
     * @param size of matrix (number of rows or columns)
     * @return determinant of matrix
     */
    double countDeterminant(const std::vector <std::vector <double>> &matrix, size_t size) const;
protected:
    /** @var count of rows */
    size_t m_rows;
    /** @var count of columns */
    size_t m_cols;

    /** Auxiliary method that counts max length of digits of matrix column
     * @param column in which count max length of digits
     * @return max length of digits
     * */
    size_t countMaxDigits(size_t column) const;
public:
    /**
     * Construtor to set count of rows and count of columns
     * @param numRows count of rows
     * @param numCols count of columns
     */
    Matrix(size_t numRows, size_t numCols);
    /** Virtual destructor */
    virtual ~Matrix() = default;
    /**
     * Method to get count of rows
     * @return count of rows
     */
    size_t numRows() const;
    /**
     * Method to get count of columns
     * @return count of columns
     */
    size_t numCols() const;
    /**
     * Virtual method to count rank of matrix
     * @return rank of matrix
     */
    virtual size_t rank() const;
    /**
     * Virtual method to count determinant of matrix
     * @return determinant of matrix
     * @throw MatrixException if determinant cannot be counted (matrix is not square)
     */
    virtual double determinant() const;
    /**
     * Virtual method to get some value of matrix
     * @param row of value
     * @param col of value
     * @return value of matrix
     */
    virtual double getVal(size_t row, size_t col) const = 0;
    /**
     * Virtual method to make deep copy of matrix
     * @return shared smart-pointer on matrix copy
     */
    virtual std::shared_ptr<Matrix> clone() const = 0;
    /**
     * Virtual method to get information about matrix
     * @param matrixName information to get
     * @return string that contains information about matrix
     */
    virtual std::string print(const std::string &matrixName) const = 0;
    /**
     * Virtual method to get information about matrix to export it in file
     * @param matrixName information to get
     * @return string that contains information about matrix in handy way
     */
    virtual std::string printToFile(const std::string &matrixName) const = 0;
};

#endif //PA2_MATRIX_H