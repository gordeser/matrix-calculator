//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_GAUSSELIMINATIONOPERATION_H
#define PA2_GAUSSELIMINATIONOPERATION_H

#include "Operation.h"

class GaussEliminationOperation : public Operation {
    std::shared_ptr<Matrix> execute(const std::shared_ptr<Matrix> &a) override;
};

#endif //PA2_GAUSSELIMINATIONOPERATION_H
