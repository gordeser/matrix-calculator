//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_GAUSSELIMINATIONOPERATION_H
#define PA2_GAUSSELIMINATIONOPERATION_H

#include "Operation.h"
#include "../Utilities.h"

class GaussEliminationOperation : public Operation {
    /**
     * Method to make matrix in reduced row echelon form
     * @param matrix values of matrix
     */
    void reduceRowEchelon(std::vector <std::vector <double>> &matrix) const;
public:
    /**
     * Constructor to set matrix
     * @param lhs matrix on left hand side
     */
    explicit GaussEliminationOperation(std::shared_ptr <Matrix> lhs);
    /**
     * Overridden method to execute gauss elimination method
     * @return values of matrix after operation
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_GAUSSELIMINATIONOPERATION_H
