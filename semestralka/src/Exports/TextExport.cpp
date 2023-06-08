//
// Created by gordeser on 15.05.2023.
//

#include <fstream>
#include "TextExport.h"
#include "../Exceptions/ExporterException.h"


void TextExport::exportData(const std::string &filename, const std::vector<std::string> &names, const MatrixStorage &storage) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
        throw ExporterException("Cannot open the file\n");

    for (const auto &name : names) {
        std::string output = storage.getMatrix(name)->printToFile(name);
        outputFile << output << "\n";
        if (!outputFile.good() || outputFile.bad() || outputFile.fail())
            throw ExporterException("Cannot write to the file\n");
    }

    outputFile.close();
    if (outputFile.is_open())
        throw ExporterException("Cannot close the file\n");
}
