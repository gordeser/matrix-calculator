//
// Created by gordeser on 15.05.2023.
//

#include "SubtractionOperation.h"
#include "../Exception.h"

std::vector <std::vector <double>> SubtractionOperation::execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) {
    if (a->numRows() != b->numRows() || a->numCols() != b->numCols()) {
        throw Exception("error");
    }

    std::vector <std::vector <double>> result (a->numRows(), std::vector <double> (a->numCols(), 0));
    for (size_t i = 0; i < a->numRows(); ++i) {
        for (size_t j = 0; j < a->numCols(); ++j) {
            result[i][j] = a->getVal(i, j) - b->getVal(i, j);
        }
    }
    return result;
}