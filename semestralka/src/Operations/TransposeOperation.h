//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TRANSPOSEOPERATION_H
#define PA2_TRANSPOSEOPERATION_H

#include "Operation.h"

class TransposeOperation : public Operation {
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a) override;
};

#endif //PA2_TRANSPOSEOPERATION_H
