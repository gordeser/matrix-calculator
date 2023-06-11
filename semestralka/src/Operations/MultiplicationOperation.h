//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_MULTIPLICATIONOPERATION_H
#define PA2_MULTIPLICATIONOPERATION_H

#include "BinaryOperation.h"

class MultiplicationOperation : public BinaryOperation {
public:
    /**
     * Constructor to set matrices
     * @param lhs matrix on left hand side
     * @param rhs matrix on right hand side
     */
    MultiplicationOperation(std::shared_ptr <Matrix> lhs, std::shared_ptr <Matrix> rhs);
    /**
     * Overridden method to execute multiplication operation
     * @return values of matrix after operation
     * @throw OperationException if number of lhs matrix columns is not equal to number of rhs matrix rows
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_MULTIPLICATIONOPERATION_H
