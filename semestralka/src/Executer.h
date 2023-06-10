//
// Created by duama on 10.06.2023.
//

#ifndef PA2_EXECUTER_H
#define PA2_EXECUTER_H


#include "Matrices/Matrix.h"
#include "Utilities.h"
#include "MatrixStorage.h"

class Executer {
    /** @var use createMatrix */
    Utilities m_utilities;
public:
    /**
     * Method that execute given operations on matrices
     * @param operations that need to be executed
     * @param storage to take elements from
     * @return shared smart-pointer to the matrix after executed operations
     * @throw ExecuterException if operation could not be executed (due invalid order)
     */
    std::shared_ptr<Matrix> executeOperations(std::vector<std::string> &elements, const MatrixStorage &storage) const;
};


#endif //PA2_EXECUTER_H
