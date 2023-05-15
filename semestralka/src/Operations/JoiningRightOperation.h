//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_JOININGRIGHTOPERATION_H
#define PA2_JOININGRIGHTOPERATION_H

#include "BinaryOperation.h"

class JoiningRightOperation : public BinaryOperation {
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) override;
};

#endif //PA2_JOININGRIGHTOPERATION_H
