//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXPONENTIATIONOPERATION_H
#define PA2_EXPONENTIATIONOPERATION_H

#include "BinaryOperation.h"
#include "../Utilities.h"

class ExponentiationOperation : public Operation {
    Utilities m_utilities;
protected:
    int m_rhs;
public:
    ExponentiationOperation(const std::shared_ptr<Matrix> &lhs, int rhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_EXPONENTIATIONOPERATION_H
