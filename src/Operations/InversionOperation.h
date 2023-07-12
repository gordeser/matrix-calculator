//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_INVERSIONOPERATION_H
#define PA2_INVERSIONOPERATION_H

#include "Operation.h"
#include "../Utilities.h"

class InversionOperation : public Operation {
    /**
     * Method to inverse the matrix
     * @param matrix after inversion
     * @throw OperationException if matrix is singular
     */
    void inverse(std::vector<std::vector <double>> &matrix) const;
public:
    /**
     * Constructor to set matrix
     * @param lhs matrix on left hand side
     */
    explicit InversionOperation(std::shared_ptr <Matrix> lhs);
    /**
     * Overridden method to execute inversion operation
     * @return values of matrix after operation
     * @throw OperationException if matrix is not square or matrix determinant is zero
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_INVERSIONOPERATION_H
