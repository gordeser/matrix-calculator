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

void TextExport::importData(const std::vector<std::string> &filenames, MatrixStorage &storage) {
    for (const auto &filename : filenames) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open())
            throw ExporterException("Cannot open the file " + filename + "\n");

        std::string input;
        std::getline(inputFile, input);
        while (!inputFile.eof()) {
            if (!inputFile.good() || inputFile.bad() || inputFile.fail())
                throw ExporterException("Cannot read from the file\n");

            auto tokens = m_utilities.tokeniseInput(input);
            if (tokens.size() < 4)
                throw ExporterException("Invalid file's content\n");

            std::string name = tokens[0];
            std::string type = tokens[1];
            if (type != "d" and type != "i" and type != "s")
                throw ExporterException("Invalid type of matrix\n");

            std::string rows = tokens[2];
            size_t numRows;
            try {
                numRows = std::stoull(rows);
            } catch (std::invalid_argument &e) {
                throw ExporterException("Invalid number of rows\n");
            } catch (std::out_of_range &e) {
                throw ExporterException("Row number is too large\n");
            }

            std::string cols = tokens[3];
            size_t numCols;
            try {
                numCols = std::stoull(cols);
            } catch (std::invalid_argument &e) {
                throw ExporterException("Invalid number of columns\n");
            } catch (std::out_of_range &e) {
                throw ExporterException("Columns number is too large\n");
            }
            std::vector <std::string> values(tokens.begin()+4, tokens.end());
            std::vector <std::vector <double>> matrix(numRows, std::vector<double>(numCols, 0));

            if (type == "d" and values.size() == numRows * numCols) {
                size_t cntElem = 0;
                for (size_t i = 0; i < numRows; ++i) {
                    for (size_t j = 0; j < numCols; ++j) {
                        double toInsert;
                        try {
                            toInsert = std::stod(values[cntElem]);
                        } catch (std::invalid_argument &e) {
                            throw ExporterException("Invalid values of matrix\n");
                        } catch (std::out_of_range &e) {
                            throw ExporterException("Matrix values are too large\n");
                        }
                        matrix[i][j] = toInsert;
                    }
                }

            } else if (type == "i" and values.size() == 0) {
                if (numRows != numCols)
                    throw ExporterException("Identical matrix should have equal number of rows and columns\n");

                for (size_t i = 0; i < numRows; ++i)
                    matrix[i][i] = 1;

            } else if (type == "s" and values.size() <= 3 * ((numCols*numRows)/2)) {
                if (values.size() % 3 != 0)
                    throw ExporterException("Invalid values of sparse matrix\n");

                for (size_t k = 0; k < values.size(); k += 3) {
                    size_t first;
                    size_t second;
                    double third;
                    try {
                        first = std::stoull(values[k]);
                        second = std::stoull(values[k+1]);
                        third = std::stod(values[k+2]);
                    } catch (std::invalid_argument &e) {
                        throw ExporterException("Invalid values of sparse matrix\n");
                    } catch (std::out_of_range &e) {
                        throw ExporterException("Matrix values is too large\n");
                    }
                    matrix[first][second] = third;
                }
            } else
                throw ExporterException("Invalid values of matrix\n");

            auto result = m_utilities.createMatrix(matrix);
            storage.addMatrix(name, result);
            getline(inputFile, input);
        }
    }
}
