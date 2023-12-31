//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TRANSPOSEOPERATION_H
#define PA2_TRANSPOSEOPERATION_H

#include "Operation.h"

class TransposeOperation : public Operation {
public:
    /**
     * Constructor to set matrix
     * @param lhs matrix on left hand side
     */
    explicit TransposeOperation(std::shared_ptr <Matrix> lhs);
    /**
     * Overridden method to execute transpose operation
     * @return values of matrix after operation
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_TRANSPOSEOPERATION_H
