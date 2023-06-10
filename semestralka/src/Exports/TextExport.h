//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TEXTEXPORT_H
#define PA2_TEXTEXPORT_H

#include "Export.h"
#include "../Utilities.h"

/** @class inherits from class Export to represent text type of export */
class TextExport : public Export {
    /** @var to contain some useful utilities */
    Utilities m_utilities;
public:
    /**
     * Method that exports matrices to file in text way
     * @param filename to export matrices
     * @param names vector of matrices to export
     * @param storage to export from
     */
    void exportData(const std::string &filename, const std::vector <std::string> &names, const MatrixStorage &storage) override;
    /**
     * Method that imports matrices from file in text way
     * @param filename to import matrices from
     * @param storage to import
     */
    void importData(const std::string &filename, MatrixStorage &storage) override;
};

#endif //PA2_TEXTEXPORT_H
