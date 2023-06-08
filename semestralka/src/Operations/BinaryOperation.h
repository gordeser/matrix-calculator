//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_BINARYOPERATION_H
#define PA2_BINARYOPERATION_H

#include "Operation.h"

class BinaryOperation : public Operation {
protected:
    std::shared_ptr <Matrix> m_rhs;
public:
    BinaryOperation(std::shared_ptr <Matrix> lhs, std::shared_ptr <Matrix> rhs);
    virtual std::vector <std::vector <double>> execute() = 0;
};


#endif //PA2_BINARYOPERATION_H
