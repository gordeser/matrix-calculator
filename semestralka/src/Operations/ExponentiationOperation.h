//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXPONENTIATIONOPERATION_H
#define PA2_EXPONENTIATIONOPERATION_H

#include "BinaryOperation.h"
#include "../Utilities.h"

class ExponentiationOperation : public Operation {
    /** @var to use createMatrix method */
    Utilities m_utilities;
protected:
    /** @var degree on right hand side */
    int m_rhs;
public:
    /**
     * Constructor to set matrix and it's degree
     * @param lhs matrix on left hand side
     * @param rhs degree on right hand side
     */
    ExponentiationOperation(const std::shared_ptr<Matrix> &lhs, int rhs);
    /**
     * Overridden method to execute exponentiation operation
     * @return values of matrix after operation
     * @throw OperationException if matrix is not square
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_EXPONENTIATIONOPERATION_H
