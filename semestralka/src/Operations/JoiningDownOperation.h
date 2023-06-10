//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_JOININGDOWNOPERATION_H
#define PA2_JOININGDOWNOPERATION_H

#include "BinaryOperation.h"

class JoiningDownOperation : public BinaryOperation {
public:
    /**
     * Constructor to set matrices
     * @param lhs matrix on left hand side
     * @param rhs matrix on right hand side
     */
    JoiningDownOperation(const std::shared_ptr <Matrix> &lhs, const std::shared_ptr <Matrix> &rhs);
    /**
     * Overridden method to execute joining rows operation
     * @return values of matrix after operation
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_JOININGDOWNOPERATION_H
