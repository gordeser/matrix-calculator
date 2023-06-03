//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_JOININGDOWNOPERATION_H
#define PA2_JOININGDOWNOPERATION_H

#include <vector>
#include "BinaryOperation.h"

class JoiningDownOperation : public BinaryOperation {
    std::vector <std::vector <double>> execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) override;
};

#endif //PA2_JOININGDOWNOPERATION_H
