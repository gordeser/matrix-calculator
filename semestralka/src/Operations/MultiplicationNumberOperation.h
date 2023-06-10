//
// Created by duama on 05.06.2023.
//

#ifndef PA2_MULTIPLICATIONNUMBEROPERATION_H
#define PA2_MULTIPLICATIONNUMBEROPERATION_H

#include "Operation.h"

/** @class inherits from Operation to represent multiplication by a number operation */
class MultiplicationNumberOperation : public Operation {
protected:
    /** @var scalar on right hand side */
    double m_rhs;
public:
    /**
     * Constructor to set matrix and scalar
     * @param lhs matrix on left hand side
     * @param rhs scalar on right hand side
     */
    MultiplicationNumberOperation(const std::shared_ptr <Matrix> &lhs, double rhs);
    /**
     * Overridden method to execute multiplication by a number operation
     * @return values of matrix after operation
     */
    std::vector <std::vector <double>> execute() const override;
};


#endif //PA2_MULTIPLICATIONNUMBEROPERATION_H
