//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_ADDITIONOPERATION_H
#define PA2_ADDITIONOPERATION_H

#include "BinaryOperation.h"

class AdditionOperation : public BinaryOperation {
public:
    AdditionOperation(const std::shared_ptr <Matrix> &lhs, const std::shared_ptr <Matrix> &rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_ADDITIONOPERATION_H
