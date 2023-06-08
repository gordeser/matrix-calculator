//
// Created by gordeser on 15.05.2023.
//

#include "MatrixStorage.h"
#include "Exceptions/StorageException.h"

void MatrixStorage::addMatrix(const std::string &name, const std::shared_ptr<Matrix> &matrix) {
    m_data[name] = matrix;
}

void MatrixStorage::removeMatrix(const std::string &name) {
    if (m_data.find(name) == m_data.end())
        throw StorageException("There is no matrix with name " + name + "\n");
    m_data.erase(name);
}
