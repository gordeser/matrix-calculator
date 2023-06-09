//
// Created by duama on 04.06.2023.
//

#ifndef PA2_UTILITIES_H
#define PA2_UTILITIES_H

#include "Matrices/DenseMatrix.h"
#include "Matrices/SparseMatrix.h"
#include "Matrices/IdentityMatrix.h"

/** @class To have some useful methods */
class Utilities {
public:
    /**
     * Method that creates matrix based on given elements. Creates identity, sparse or dense matrix.
     * @param elements from which matrix will be created
     * @return shared smart-pointer on created matrix
     */
    std::shared_ptr<Matrix> createMatrix(const std::vector<std::vector <double>> &elements);
    /**
     * Method that tokenise given input by space
     * @param input to tokenise
     * @return vector of tokens
     */
    std::vector <std::string> tokeniseInput(const std::string &input);
    /**
     * Method that deletes unnecessary spaces
     * (more than one space between words and spaces before and after all words)
     * @param str string to modify
     * @return modified string
     */
    std::string deleteSpaces(const std::string &str);
    /**
     * Method that checks if given name of matrix is allowed
     * (is not one of reserved names and do not contain bad symbols)
     * @param name of matrix
     * @return true if name is allowed, false if name is not allowed
     */
    bool checkName(const std::string &name);
};


#endif //PA2_UTILITIES_H
