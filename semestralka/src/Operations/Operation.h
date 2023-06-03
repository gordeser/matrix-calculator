//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_OPERATION_H
#define PA2_OPERATION_H

#include "../Matrices/Matrix.h"

class Operation {
public:
    virtual ~Operation() {}
    virtual std::vector <std::vector <double>> execute(const std::shared_ptr<Matrix> &a) = 0;
};

#endif //PA2_OPERATION_H
