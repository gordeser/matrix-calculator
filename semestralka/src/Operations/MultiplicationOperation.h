//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_MULTIPLICATIONOPERATION_H
#define PA2_MULTIPLICATIONOPERATION_H

#include <vector>
#include "BinaryOperation.h"

class MultiplicationOperation : public BinaryOperation {
public:
    std::vector <std::vector <double>> execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) override;
    std::vector <std::vector <double>> execute(const std::shared_ptr<Matrix> &a, double b) override;
};

#endif //PA2_MULTIPLICATIONOPERATION_H
