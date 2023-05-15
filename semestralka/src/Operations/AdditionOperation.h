//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_ADDITIONOPERATION_H
#define PA2_ADDITIONOPERATION_H

#include "BinaryOperation.h"

class AdditionOperation : public BinaryOperation {
public:
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) override;
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, double b) override;
};

#endif //PA2_ADDITIONOPERATION_H