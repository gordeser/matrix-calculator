//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TRANSPOSEOPERATION_H
#define PA2_TRANSPOSEOPERATION_H

#include "Operation.h"

class TransposeOperation : public Operation {
public:
    TransposeOperation(std::shared_ptr <Matrix> lhs);
    std::vector <std::vector <double>> execute() override;
};

#endif //PA2_TRANSPOSEOPERATION_H
