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
    std::shared_ptr<Matrix> createMatrix(const std::vector<std::vector <double>> &elements);
    std::vector <std::string> tokeniseInput(const std::string &input);
    std::string deleteSpaces(const std::string &str);
    bool checkName(const std::string &name);
    bool checkTokens(const std::vector<std::string> &tokens);
};


#endif //PA2_UTILITIES_H
