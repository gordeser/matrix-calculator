//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_BINARYOPERATION_H
#define PA2_BINARYOPERATION_H

#include "Operation.h"

class BinaryOperation : public Operation {
public:
    virtual std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) = 0;
    virtual std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, double b) = 0;
    virtual std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, int b) = 0;
    virtual std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a, std::pair<std::size_t, std::size_t> &b) = 0;
};

#endif //PA2_BINARYOPERATION_H
