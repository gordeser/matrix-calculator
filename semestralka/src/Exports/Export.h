//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_EXPORT_H
#define PA2_EXPORT_H

#include <string>
#include "../Matrices/Matrix.h"
#include "../MatrixStorage.h"

class Export {
public:
    virtual ~Export() {}
    virtual void exportData(const std::string &filename, const std::vector <std::string> &names, const MatrixStorage &storage) = 0;
    virtual void importData(const std::vector<std::string> &filenames, MatrixStorage &storage) = 0;
};

#endif //PA2_EXPORT_H
