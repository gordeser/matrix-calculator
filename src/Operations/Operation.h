//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_OPERATION_H
#define PA2_OPERATION_H

#include "../Matrices/Matrix.h"

class Operation {
protected:
    /** @var matrix on left hand side */
    std::shared_ptr<Matrix> m_lhs;
public:
    /**
     * Constructor to set matrix on left hand side
     * @param lhs left hand side matrix
     */
    explicit Operation(std::shared_ptr<Matrix> lhs);
    /** Virtual destructor */
    virtual ~Operation() = default;
    /**
     * Virtual method that executes operation
     * @return values of matrix after operation
     */
    virtual std::vector <std::vector <double>> execute() const = 0;
};


#endif //PA2_OPERATION_H
