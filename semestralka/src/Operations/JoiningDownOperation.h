//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_JOININGDOWNOPERATION_H
#define PA2_JOININGDOWNOPERATION_H

#include "BinaryOperation.h"

class JoiningDownOperation : public BinaryOperation {
public:
    JoiningDownOperation(const std::shared_ptr <Matrix> &lhs, const std::shared_ptr <Matrix> &rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_JOININGDOWNOPERATION_H
