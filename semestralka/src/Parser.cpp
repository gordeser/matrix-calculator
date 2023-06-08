//
// Created by gordeser on 15.05.2023.
//

#include "Parser.h"
#include "Commands.h"
#include "Operations/AdditionOperation.h"
#include "Operations/ExponentiationOperation.h"
#include "Operations/GaussEliminationOperation.h"
#include "Operations/InversionOperation.h"
#include "Operations/JoiningDownOperation.h"
#include "Operations/JoiningRightOperation.h"
#include "Operations/MultiplicationNumberOperation.h"
#include "Operations/MultiplicationOperation.h"
#include "Operations/SubtractionOperation.h"
#include "Operations/TransposeOperation.h"
#include "Operations/TrimmingOperation.h"
#include "Exceptions/ParserException.h"


void Parser::deleteElements(const std::vector<std::string> &elements) {
    for (const auto &elem : elements)
        m_storage.removeMatrix(elem);
}

void Parser::deleteAllElements() {
    m_storage.removeAllMatrices();
}

void Parser::importElements(const std::vector<std::string> &elements) {
    m_textexport.importData(elements, m_storage);
}

void Parser::scanElements(const std::string &name) {
    m_console.showText("Input size of matrix: ");
    std::string input = m_utilities.deleteSpaces(m_console.getInput());
    size_t numRows, numCols;
    char c;
    std::stringstream ss(input);
    if (!(ss >> numRows >> numCols))
        throw ParserException("There should be only number of rows and number of columns");

    if (ss >> c)
        throw ParserException("There should be only number of rows and number of columns");

    std::vector <std::vector <double>> elements(numRows, std::vector<double> (numCols, 0));

    for (size_t i = 0; i < numRows; ++i) {
        m_console.showText("Input " + std::to_string(i+1) + " row of matrix: ");

        auto row = m_utilities.tokeniseInput(m_console.getInput());
        if (row.size() != numCols)
            throw ParserException("One row must have " + std::to_string(numCols) + " elements");

        for (size_t j = 0; j < numCols; ++j)
            elements[i][j] = std::stod(row[j]);
    }
    auto matrix = m_utilities.createMatrix(elements);
    m_storage.addMatrix(name, matrix);
}

void Parser::printDet(const std::vector<std::string> &elements) {
    for (const auto &elem : elements) {
        double det = m_storage.getMatrix(elem)->determinant();
        std::ostringstream ss;
        ss << "Determinant of matrix " << elem << " is " << det << + "\n";
        m_console.showText(ss.str());
    }
}

void Parser::printRank(const std::vector<std::string> &elements) {
    for (const auto &elem : elements) {
        size_t rank = m_storage.getMatrix(elem)->rank();
        std::ostringstream ss;
        ss << "Rank of matrix " << elem << " is " << rank << "\n";
        m_console.showText(ss.str());
    }
}
