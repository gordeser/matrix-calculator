//
// Created by gordeser on 15.05.2023.
//

#include "MultiplicationOperation.h"
#include "../Exception.h"

std::vector <std::vector <double>> MultiplicationOperation::execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) {
    if (a->numCols() != b->numRows())
        throw Exception("error");

    std::vector <std::vector <double>> result(a->numRows(), std::vector <double> (b->numCols(), 0));

    for (size_t i = 0; i < a->numRows(); ++i) {
        for (size_t j = 0; j < b->numCols(); ++j) {
            double sum = 0;
            for (size_t k = 0; k < a->numCols(); ++k) {
                sum += a->getVal(i, k) * b->getVal(k, j);
            }
            result[i][j] = sum;
        }
    }
    return result;
}

std::vector <std::vector <double>> MultiplicationOperation::execute(const std::shared_ptr<Matrix> &a, double b) {
    std::vector <std::vector <double>> result(a->numRows(), std::vector<double> (a->numCols(), 0));
    for (size_t i = 0; i < a->numRows(); ++i) {
        for (size_t j = 0; j < a->numCols(); ++j) {
            result[i][j] = a->getVal(i, j) * b;
        }
    }
    return result;
}
