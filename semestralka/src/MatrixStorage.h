//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_MATRIXSTORAGE_H
#define PA2_MATRIXSTORAGE_H

#include <map>
#include <string>
#include "Matrices/Matrix.h"

class MatrixStorage {
    /** @var map to save the data, where key is matrix name and value is Matrix shared smart-pointer */
    std::map <std::string, std::shared_ptr<Matrix>> m_data;
public:
    /**
     * Method that adds matrix to the database
     * @param name of matrix
     * @param matrix shared smart-pointer
     */
    void addMatrix(const std::string &name, const std::shared_ptr<Matrix> &matrix);
    /**
     * Method that removes matrix from the database, throws StorageException if there is no matrix with that name
     * @param name of matrix
     * @throw StorageException if there is no matrix with given name
     */
    void removeMatrix(const std::string &name);
    /** Method that removes all matrices from the database */
    void removeAllMatrices();
    /**
     * Method to get shared smart-pointer to the matrix with some name, throws StorageException if there is no matrix with that name
     * @param name of matrix
     * @return shared smart-pointer to the matrix with that name
     * @throw StorageException if there is no matrix with given name
     */
    std::shared_ptr<Matrix> getMatrix(const std::string &name) const;
    /**
     * Method to get all matrix names in database, throws StorageException if there is no matrices in database
     * @return vector of matrices' names
     * @throw StorageException if there is no matrices in database
     */
    std::vector <std::string> getAllMatrices() const;
};

#endif //PA2_MATRIXSTORAGE_H
