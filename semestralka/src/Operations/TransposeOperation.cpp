//
// Created by gordeser on 15.05.2023.
//

#include "TransposeOperation.h"

std::vector <std::vector <double>> TransposeOperation::execute(const std::shared_ptr<Matrix> &a) {
    std::vector <std::vector <double>> result(a->numRows(), std::vector<double> (a->numCols(), 0));
    for (size_t i = 0; i < a->numRows(); ++i) {
        for (size_t j = 0; j < a->numCols(); ++j) {
            result[i][j] = a->getVal(j, i);
        }
    }
    return result;
}
