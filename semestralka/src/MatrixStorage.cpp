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

void MatrixStorage::removeAllMatrices() {
    m_data.clear();
}

std::shared_ptr<Matrix> MatrixStorage::getMatrix(const std::string &name) const {
    if (m_data.find(name) == m_data.end())
        throw StorageException("There is no matrix with name " + name + "\n");
    return m_data.at(name);
}

std::vector <std::string> MatrixStorage::getAllMatrices() const {
    std::vector <std::string> names;

    if (m_data.size() == 0)
        throw StorageException("There are no matrices in database\n");

    for (const auto &matrix : m_data)
        names.push_back(matrix.first);
    return names;
}