//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_INVERSIONOPERATION_H
#define PA2_INVERSIONOPERATION_H

#include "Operation.h"
#include "../Utilities.h"

class InversionOperation : public Operation {
    Utilities m_utilities;
    void swapRows(std::vector<std::vector <double>> &matrix, size_t firstRow, size_t secondRow);
    void scaleRow(std::vector<std::vector <double>> &matrix, size_t row, double number);
    void addScaledRow(std::vector<std::vector <double>> &matrix, size_t sourceRow, size_t targetRow, double number);
    void inverse(std::vector<std::vector <double>> &matrix);
public:
    InversionOperation(const std::shared_ptr <Matrix> &rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_INVERSIONOPERATION_H
