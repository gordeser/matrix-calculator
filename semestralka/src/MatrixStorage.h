//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_MATRIXSTORAGE_H
#define PA2_MATRIXSTORAGE_H

#include <map>
#include <string>
#include "Matrices/Matrix.h"

class MatrixStorage {
    std::map <std::string, std::shared_ptr<Matrix>> m_data;
public:
    void addMatrix(const std::string &name, const std::shared_ptr<Matrix> &matrix);
    void removeMatrix(const std::string &name);
    void removeAllMatrices();
    std::shared_ptr<Matrix> getMatrix(const std::string &name) const;
    std::vector <std::string> getAllMatrices();
};

#endif //PA2_MATRIXSTORAGE_H
