//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_ADDITIONOPERATION_H
#define PA2_ADDITIONOPERATION_H

#include "BinaryOperation.h"

class AdditionOperation : public BinaryOperation {
public:
    /**
     * Constructor to set left and right hand side matrices
     * @param lhs left hand side matrix
     * @param rhs right hand side matrix
     */
    AdditionOperation(std::shared_ptr <Matrix> lhs, std::shared_ptr <Matrix> rhs);
    /**
     * Overridden method that executes addition operation
     * @return matrix values after addition operation
     * @throw OperationException if number of rows or columns are not equal
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_ADDITIONOPERATION_H
