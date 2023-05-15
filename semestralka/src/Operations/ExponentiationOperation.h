//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXPONENTIATIONOPERATION_H
#define PA2_EXPONENTIATIONOPERATION_H

#include "BinaryOperation.h"

class ExponentiationOperation : public BinaryOperation {
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, int b) override;
};

#endif //PA2_EXPONENTIATIONOPERATION_H
