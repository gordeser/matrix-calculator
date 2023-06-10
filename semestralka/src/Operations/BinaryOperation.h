//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_BINARYOPERATION_H
#define PA2_BINARYOPERATION_H

#include "Operation.h"

/** @class Abstract class that inherits from class Operation to represent binary operation */
class BinaryOperation : public Operation {
protected:
    /** @var matrix on right hand side */
    std::shared_ptr <Matrix> m_rhs;
public:
    /**
     * Constructor to set matrices on left and right hand sides
     * @param lhs left hand side matrix
     * @param rhs right hand side matrix
     */
    BinaryOperation(std::shared_ptr <Matrix> lhs, std::shared_ptr <Matrix> rhs);
    /**
     * Virtual method that executes operation
     * @return values of matrix after operation
     */
    virtual std::vector <std::vector <double>> execute() = 0;
};


#endif //PA2_BINARYOPERATION_H
