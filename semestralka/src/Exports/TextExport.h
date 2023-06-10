//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TEXTEXPORT_H
#define PA2_TEXTEXPORT_H

#include "Export.h"
#include "../Utilities.h"

class TextExport : public Export {
    /** @var to contain some useful utilities */
    Utilities m_utilities;
public:
    /**
     * Overridden Method that exports matrices to file in text way
     * @param filename to export matrices
     * @param names vector of matrices to export
     * @param storage to export from
     * @throw ExporterException if cannot open or close the file or write to file
     */
    void exportData(const std::string &filename, const std::vector <std::string> &names, const MatrixStorage &storage) const override;
    /**
     * Overridden method that imports matrices from file in text way
     * @param filename to import matrices from
     * @param storage to import
     * @throw ExporterException if cannot open or close the file, cannot read from file, there is invalid data or values are too large
     */
    void importData(const std::string &filename, MatrixStorage &storage) override;
};

#endif //PA2_TEXTEXPORT_H
