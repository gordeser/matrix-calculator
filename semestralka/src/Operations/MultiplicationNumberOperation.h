//
// Created by duama on 05.06.2023.
//

#ifndef PA2_MULTIPLICATIONNUMBEROPERATION_H
#define PA2_MULTIPLICATIONNUMBEROPERATION_H

#include "Operation.h"

class MultiplicationNumberOperation : public Operation {
protected:
    double m_rhs;
public:
    MultiplicationNumberOperation(const std::shared_ptr <Matrix> &lhs, double rhs);
    std::vector <std::vector <double>> execute() override;
};


#endif //PA2_MULTIPLICATIONNUMBEROPERATION_H
