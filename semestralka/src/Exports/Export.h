//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXPORT_H
#define PA2_EXPORT_H

#include <string>
#include "../Matrices/Matrix.h"

class Export {
public:
    virtual ~Export() {}
    virtual void exportData(const std::shared_ptr<Matrix> &matrix, const std::string &filename) = 0;
};

#endif //PA2_EXPORT_H
