//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_BINARYOPERATION_H
#define PA2_BINARYOPERATION_H

#include "Operation.h"

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
};


#endif //PA2_BINARYOPERATION_H
