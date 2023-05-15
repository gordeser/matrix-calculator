//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TRIMMINGOPERATION_H
#define PA2_TRIMMINGOPERATION_H

#include "BinaryOperation.h"

class TrimmingOperation : public BinaryOperation {
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, std::pair<std::size_t, std::size_t> &b);
};

#endif //PA2_TRIMMINGOPERATION_H
