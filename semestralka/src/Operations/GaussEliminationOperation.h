//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_GAUSSELIMINATIONOPERATION_H
#define PA2_GAUSSELIMINATIONOPERATION_H

#include "Operation.h"

class GaussEliminationOperation : public Operation {
    void swapRows(std::vector<std::vector <double>> &matrix, size_t firstRow, size_t secondRow);
    void scaleRow(std::vector<std::vector <double>> &matrix, size_t row, double number);
    void addScaledRow(std::vector<std::vector <double>> &matrix, size_t sourceRow, size_t targetRow, double number);
    void reduceRowEchelon(std::vector <std::vector <double>> &matrix);
public:
    GaussEliminationOperation(const std::shared_ptr <Matrix> &lhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_GAUSSELIMINATIONOPERATION_H
