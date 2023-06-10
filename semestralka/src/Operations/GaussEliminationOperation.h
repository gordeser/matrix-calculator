//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_GAUSSELIMINATIONOPERATION_H
#define PA2_GAUSSELIMINATIONOPERATION_H

#include "Operation.h"

/** @class inherits from Operation to represent Gauss Elimination Method */
class GaussEliminationOperation : public Operation {
    /**
     * Method to swap two rows of matrix
     * @param matrix values of matrix
     * @param firstRow to swap
     * @param secondRow to swap
     */
    void swapRows(std::vector<std::vector <double>> &matrix, size_t firstRow, size_t secondRow) const;
    /**
     * Method to scale row by a number
     * @param matrix values of matrix
     * @param row to scale
     * @param number scalar
     */
    void scaleRow(std::vector<std::vector <double>> &matrix, size_t row, double number) const;
    /**
     * Method to scale row and add it's values to another row
     * @param matrix values of matrix
     * @param sourceRow to scale it's values
     * @param targetRow to add scaled values
     * @param number scalar
     */
    void addScaledRow(std::vector<std::vector <double>> &matrix, size_t sourceRow, size_t targetRow, double number) const;
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
    GaussEliminationOperation(const std::shared_ptr <Matrix> &lhs);
    /**
     * Overridden method to execute gauss elimination method
     * @return values of matrix after operation
     */
    std::vector <std::vector <double>> execute() const override;
};

#endif //PA2_GAUSSELIMINATIONOPERATION_H
