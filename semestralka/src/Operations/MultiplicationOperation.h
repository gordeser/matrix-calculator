//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_MULTIPLICATIONOPERATION_H
#define PA2_MULTIPLICATIONOPERATION_H

#include "BinaryOperation.h"

class MultiplicationOperation : public BinaryOperation {
public:
    MultiplicationOperation(const std::shared_ptr <Matrix> &lhs, const std::shared_ptr <Matrix> &rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_MULTIPLICATIONOPERATION_H
