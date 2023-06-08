//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_SUBTRACTIONOPERATION_H
#define PA2_SUBTRACTIONOPERATION_H

#include "BinaryOperation.h"

class SubtractionOperation  : public BinaryOperation {
public:
    SubtractionOperation(const std::shared_ptr<Matrix> &lhs, const std::shared_ptr<Matrix> &rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_SUBTRACTIONOPERATION_H
