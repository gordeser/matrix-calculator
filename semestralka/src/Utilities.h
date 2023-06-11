//
// Created by duama on 04.06.2023.
//

#ifndef PA2_UTILITIES_H
#define PA2_UTILITIES_H

#include "Matrices/DenseMatrix.h"
#include "Matrices/SparseMatrix.h"
#include "Matrices/IdentityMatrix.h"

class Utilities {
public:
    /**
     * Method that creates matrix based on given elements. Creates identity, sparse or dense matrix.
     * @param elements from which matrix will be created
     * @return shared smart-pointer on created matrix
     */
    static std::shared_ptr<Matrix> createMatrix(const std::vector<std::vector <double>> &elements);
    /**
     * Method that tokenise given input by space
     * @param input to tokenise
     * @return vector of tokens
     */
    static std::vector <std::string> tokeniseInput(const std::string &input);
    /**
     * Method that deletes unnecessary spaces
     * (more than one space between words and spaces before and after all words)
     * @param str string to modify
     * @return modified string
     */
    static std::string deleteSpaces(const std::string &str);
    /**
     * Method that checks if given name of matrix is allowed
     * (is not one of reserved names and do not contain bad symbols)
     * @param name of matrix
     * @return true if name is allowed, false if name is not allowed
     */
    static bool checkName(const std::string &name);
    /**
     * Method to swap two rows of matrix
     * @param matrix values of matrix
     * @param firstRow to swap
     * @param secondRow to swap
     */
    static void swapRows(std::vector<std::vector<double>> &matrix, size_t firstRow, size_t secondRow);
    /**
     * Method to scale row by a number
     * @param matrix values of matrix
     * @param row to scale
     * @param number scalar
     */
    static void scaleRow(std::vector<std::vector <double>> &matrix, size_t row, double number);
    /**
     * Method to scale row and add it's values to another row
     * @param matrix values of matrix
     * @param sourceRow to scale it's values
     * @param targetRow to add scaled values
     * @param number scalar
     */
    static void addScaledRow(std::vector<std::vector <double>> &matrix, size_t sourceRow, size_t targetRow, double number);

};


#endif //PA2_UTILITIES_H
