//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_OPERATION_H
#define PA2_OPERATION_H

#include "../Matrices/Matrix.h"

class Operation {
protected:
    std::shared_ptr<Matrix> m_lhs;
public:
    Operation(std::shared_ptr<Matrix> lhs);
    virtual ~Operation() {}
    virtual std::vector <std::vector <double>> execute() = 0;
};


#endif //PA2_OPERATION_H
