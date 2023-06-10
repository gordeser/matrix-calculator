//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXPORT_H
#define PA2_EXPORT_H

#include <string>
#include "../Matrices/Matrix.h"
#include "../MatrixStorage.h"

/** @class Abstract class that represents types of export (text, binary, ...) */
class Export {
public:
    /** Virtual Destructor */
    virtual ~Export() {}
    /**
     * Virtual method that exports matrices to file
     * @param filename to export matrices
     * @param names vector of matrices to export
     * @param storage to export from
     */
    virtual void exportData(const std::string &filename, const std::vector <std::string> &names, const MatrixStorage &storage) const = 0;
    /**
     * Virtaul method that imports matrices from file
     * @param filename to import matrices from
     * @param storage to import
     */
    virtual void importData(const std::string &filename, MatrixStorage &storage) = 0;
};

#endif //PA2_EXPORT_H
