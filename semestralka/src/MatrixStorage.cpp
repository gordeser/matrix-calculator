//
// Created by gordeser on 15.05.2023.
//

#include "MatrixStorage.h"
#include "Exceptions/StorageException.h"

void MatrixStorage::addMatrix(const std::string &name, const std::shared_ptr<Matrix> &matrix) {
    m_data[name] = matrix;
}
