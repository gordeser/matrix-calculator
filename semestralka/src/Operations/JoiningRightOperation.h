//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_JOININGRIGHTOPERATION_H
#define PA2_JOININGRIGHTOPERATION_H

#include "BinaryOperation.h"

class JoiningRightOperation : public BinaryOperation {
public:
    JoiningRightOperation(const std::shared_ptr <Matrix> &lhs, const std::shared_ptr <Matrix> &rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_JOININGRIGHTOPERATION_H
