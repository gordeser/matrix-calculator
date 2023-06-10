//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_MULTIPLICATIONOPERATION_H
#define PA2_MULTIPLICATIONOPERATION_H

#include "BinaryOperation.h"

/** @class inherits from BinaryOperation to represent multiplication operation */
class MultiplicationOperation : public BinaryOperation {
public:
    /**
     * Constructor to set matrices
     * @param lhs matrix on left hand side
     * @param rhs matrix on right hand side
     */
    MultiplicationOperation(const std::shared_ptr <Matrix> &lhs, const std::shared_ptr <Matrix> &rhs);
    /**
     * Overridden method to execute multiplication operation
     * @return values of matrix after operation
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_MULTIPLICATIONOPERATION_H
