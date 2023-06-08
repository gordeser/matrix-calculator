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

void Parser::parseInput(std::string input) {
    auto tokens = m_utilities.tokeniseInput(input);

    if (tokens.empty()) return;
    std::string command = tokens[0];

    if (command == Commands::HELP) {
        printHelp();
        return;
    } else if (command == Commands::PRINT) {
        if (tokens.size() < 2)
            throw ParserException("USAGE: print <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> elements(tokens.begin()+1, tokens.end());

        for (const auto &elem : elements)
            if (!m_utilities.checkName(elem))
                throw ParserException("You have entered bad matrix name\n");

        printElements(elements);
        return;
    } else if (command == Commands::PRINTALL) {
        printAllElements();
        return;
    } else if (command == Commands::EXPORT) {
        if (tokens.size() < 3)
            throw ParserException("USAGE: export <filename> <matrix1, matrix2, ..., matrix_n>\n");

        std::string filename = tokens[1];
        std::vector <std::string> elements(tokens.begin()+2, tokens.end());

        for (const auto &elem : elements)
            if (!m_utilities.checkName(elem))
                throw ParserException("You have entered bad matrix name\n");

        exportElements(filename, elements);
        return;
    } else if (command == Commands::EXPORTALL) {
        if (tokens.size() < 2)
            throw ParserException("USAGE: exportall <filename>\n");

        std::string filename = tokens[1];
        exportAllElements(filename);
        return;
    } else if (command == Commands::DEL) {
        if (tokens.size() < 2)
            throw ParserException("USAGE: del <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> elements(tokens.begin()+1, tokens.end());
        for (const auto &elem : elements)
            if (!m_utilities.checkName(elem))
                throw ParserException("You have entered bad matrix name\n");

        deleteElements(elements);
        return;
    } else if (command == Commands::DELALL) {
        deleteAllElements();
        return;
    } else if (command == Commands::IMPORT) {
        if (tokens.size() < 2)
            throw ParserException("USAGE: import <filename1, filename2, ..., filename_n>\n");

        std::vector <std::string> elements(tokens.begin()+1, tokens.end());

        importElements(elements);
        return;
    } else if (command == Commands::SCAN) {
        if (tokens.size() != 2)
            throw ParserException("USAGE: scan <matrix>\n");

        std::string name = tokens[1];
        if (!m_utilities.checkName(name))
            throw ParserException("You have entered bad matrix name\n");

        scanElements(name);
        return;
    } else if (command == Commands::DET) {
        if (tokens.size() < 2)
            throw ParserException("USAGE: det <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> elements(tokens.begin()+1, tokens.end());
        for (const auto &elem : elements)
            if (!m_utilities.checkName(elem))
                throw ParserException("You have entered bad matrix name\n");

        printDet(elements);
        return;
    } else if (command == Commands::RANK) {
        if (tokens.size() < 2)
            throw ParserException("USAGE: rank <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> elements(tokens.begin()+1, tokens.end());
        for (const auto &elem : elements)
            if (!m_utilities.checkName(elem))
                throw ParserException("You have entered bad matrix name\n");

        printRank(elements);
        return;
    } else if (tokens.size() >= 3 and tokens[1] == "=") {
        std::string name = tokens[0];

        if (!m_utilities.checkName(name))
            throw ParserException("You have entered bad matrix name\n");

        std::vector <std::string> operations(tokens.begin()+2, tokens.end());

        if (!m_utilities.checkTokens(operations))
            throw ParserException("Unknown command. Try \"help\"\n");

        auto matrix = executeOperations(operations);
        if (matrix != nullptr) {
            m_storage.addMatrix(name, matrix);
            return;
        }
    } else {
        auto matrix = executeOperations(tokens);

        if (matrix != nullptr) {
            m_console.showText(matrix->print(""));
            return;
        }
    }
    throw ParserException("Unknown command. Try \"help\"\n");
}


void Parser::printElements(const std::vector<std::string> &elements) {
    for (const auto &elem : elements)
        m_console.showText(m_storage.getMatrix(elem)->print(elem));
}

void Parser::printAllElements() {
    auto allNames = m_storage.getAllMatrices();
    for (const auto &name : allNames) {
        m_console.showText(m_storage.getMatrix(name)->print(name));
        m_console.showText("------------------------------------\n");
    }
}

void Parser::exportElements(const std::string &filename, const std::vector<std::string> &elements) {
    m_textexport.exportData(filename, elements, m_storage);
}

void Parser::exportAllElements(const std::string &filename) {
    auto allNames = m_storage.getAllMatrices();
    m_textexport.exportData(filename, allNames, m_storage);
}

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
