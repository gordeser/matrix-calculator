//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TRIMMINGOPERATION_H
#define PA2_TRIMMINGOPERATION_H

#include "Operation.h"

class TrimmingOperation : public Operation {
protected:
    size_t m_rows, m_cols, m_offsetRows, m_offsetCols;
public:
    TrimmingOperation(std::shared_ptr<Matrix> &lhs, size_t rows, size_t cols, size_t offsetRows, size_t offsetCols);
    std::vector <std::vector <double>> execute();
};

#endif //PA2_TRIMMINGOPERATION_H
