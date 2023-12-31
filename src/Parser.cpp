//
// Created by gordeser on 15.05.2023.
//

#include "Parser.h"
#include "Commands.h"
#include "Exceptions/ParserException.h"

void Parser::parseInput(const std::string &input) {
    auto tokens = Utilities::tokeniseInput(input);

    if (tokens.empty()) return;
    std::string command = tokens[0];

    if (command == Commands::HELP) {
        printHelp();
        return;
    } else if (command == Commands::PRINT) {
        // if there is only print with no arguments
        if (tokens.size() < 2)
            throw ParserException("USAGE: print <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> arguments(tokens.begin()+1, tokens.end());
        for (const auto &arg : arguments)
            if (!Utilities::checkName(arg))
                throw ParserException("You have entered bad matrix name\n");
        printElements(arguments);
        return;
    } else if (command == Commands::PRINTALL) {
        printAllElements();
        return;
    } else if (command == Commands::EXPORT) {
        // if there is export without arguments
        if (tokens.size() < 3)
            throw ParserException("USAGE: export <filename> <matrix1, matrix2, ..., matrix_n>\n");

        std::string filename = tokens[1];
        std::vector <std::string> arguments(tokens.begin()+2, tokens.end());
        for (const auto &arg : arguments)
            if (!Utilities::checkName(arg))
                throw ParserException("You have entered bad matrix name\n");
        exportElements(filename, arguments);
        return;
    } else if (command == Commands::EXPORTALL) {
        // if there is only exportall without filename
        if (tokens.size() < 2)
            throw ParserException("USAGE: exportall <filename>\n");

        std::string filename = tokens[1];
        exportAllElements(filename);
        return;
    } else if (command == Commands::DEL) {
        // if there is only del without arguments
        if (tokens.size() < 2)
            throw ParserException("USAGE: del <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> arguments(tokens.begin()+1, tokens.end());
        for (const auto &arg : arguments)
            if (!Utilities::checkName(arg))
                throw ParserException("You have entered bad matrix name\n");
        deleteElements(arguments);
        return;
    } else if (command == Commands::DELALL) {
        deleteAllElements();
        return;
    } else if (command == Commands::IMPORT) {
        // if there is only import without filenames
        if (tokens.size() < 2)
            throw ParserException("USAGE: import <filename1, filename2, ..., filename_n>\n");

        std::vector <std::string> filenames(tokens.begin()+1, tokens.end());
        importElements(filenames);
        return;
    } else if (command == Commands::SCAN) {
        // if tokens are not scan and name
        if (tokens.size() != 2)
            throw ParserException("USAGE: scan <matrix>\n");

        std::string name = tokens[1];

        // check matrix name
        if (!Utilities::checkName(name))
            throw ParserException("You have entered bad matrix name\n");

        scanElements(name);
        return;
    } else if (command == Commands::DET) {
        // if there is only det without arguments
        if (tokens.size() < 2)
            throw ParserException("USAGE: det <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> arguments(tokens.begin()+1, tokens.end());
        for (const auto &arg : arguments)
            if (!Utilities::checkName(arg))
                throw ParserException("You have entered bad matrix name\n");
        printDet(arguments);
        return;
    } else if (command == Commands::RANK) {
        // if there is only rank without arguments
        if (tokens.size() < 2)
            throw ParserException("USAGE: rank <matrix1, matrix2, ..., matrix_n>\n");

        std::vector <std::string> arguments(tokens.begin()+1, tokens.end());
        for (const auto &arg : arguments)
            if (!Utilities::checkName(arg))
                throw ParserException("You have entered bad matrix name\n");
        printRank(arguments);
        return;
    } else if (tokens.size() >= 3 and tokens[1] == "=") { // if we have {var = ...}
        std::string name = tokens[0];

        if (!Utilities::checkName(name))
            throw ParserException("You have entered bad matrix name\n");

        std::vector <std::string> operations(tokens.begin()+2, tokens.end());
        auto matrix = m_executer.executeOperations(operations, m_storage);
        m_storage.addMatrix(name, matrix);
        return;
    } else {
        auto matrix = m_executer.executeOperations(tokens, m_storage);
        m_console.showText(matrix->print(""));
        return;
    }
}

void Parser::printHelp() const {
    m_console.showText("\nAll matrices and commands names are case-insensitive\n");
    m_console.showText("Matrix names have to contain ONLY alphabetic characters and numbers\n");
    m_console.showText("Matrix names cannot be the same as matrix operations' names\n\n");

    m_console.showText("- SCAN matrixName\n");
    m_console.showText("Then input count of rows and columns\n");
    m_console.showText("Then input matrix values by rows\n\n");

    m_console.showText("- IMPORT filename - Import ALL matrices from filename\n\n");

    m_console.showText("- DEL A - Delete matrix with name A\n");
    m_console.showText("- DELALL - Delete ALL matrices\n\n");

    m_console.showText("- EXPORT filename <matrix1, matrix2, ..., matrix_n> - Export matrices to the filename\n");
    m_console.showText("- EXPORTALL filename - Export ALL matrices to the filename\n\n");

    m_console.showText("- PRINT A - Display A matrix values in the console\n");
    m_console.showText("- PRINTALL - Display ALL matrices' values in the console\n\n");

    m_console.showText("- HELP - Print this message\n");
    m_console.showText("- QUIT or EXIT - Terminate the program\n\n");

    m_console.showText("Operations:\n");
    m_console.showText("- ADD A B - Add the values of matrix B to the matrix A\n");
    m_console.showText("- SUB A B - Subtract the values of matrix B from matrix A\n");
    m_console.showText("- MUL a A - Multiply the values of matrix A by a number a\n");
    m_console.showText("- MUL A B - Multiply matrix A by matrix B\n");
    m_console.showText("- JOINRIGHT A B - Join matrix B to the matrix A as columns\n");
    m_console.showText("- JOINDOWN A B - Join matrix B to the matrix A as rows\n");
    m_console.showText("- TRIM A newNumRow newNumCol offsetRow offsetCol - Trim A matrix to newNumRow and newNumCol with offsets\n");
    m_console.showText("- EXP A a - Increase matrix A to the power of a\n");
    m_console.showText("- TRANS A - Transpose matrix A\n");
    m_console.showText("- INV A - Inverse matrix A\n");
    m_console.showText("- DET A - Count determinant of matrix A\n");
    m_console.showText("- RANK A - Count rank of matrix A\n");
    m_console.showText("- GEM A - Reduce the matrix A to reduced row echelon form\n");
}

void Parser::printElements(const std::vector<std::string> &arguments) const {
    m_console.showText("------------------------------------\n");
    for (const auto &arg : arguments) {
        m_console.showText(m_storage.getMatrix(arg)->print(arg));
        m_console.showText("------------------------------------\n");
    }
}

void Parser::printAllElements() const {
    auto allNames = m_storage.getAllMatrices();
    m_console.showText("------------------------------------\n");
    for (const auto &name : allNames) {
        m_console.showText(m_storage.getMatrix(name)->print(name));
        m_console.showText("------------------------------------\n");
    }
}

void Parser::exportElements(const std::string &filename, const std::vector<std::string> &arguments) const {
    m_textexport.exportData(filename, arguments, m_storage);
}

void Parser::exportAllElements(const std::string &filename) const {
    auto allNames = m_storage.getAllMatrices();
    m_textexport.exportData(filename, allNames, m_storage);
}

void Parser::deleteElements(const std::vector<std::string> &arguments) {
    for (const auto &arg : arguments)
        m_storage.removeMatrix(arg);
}

void Parser::deleteAllElements() {
    m_storage.removeAllMatrices();
}

void Parser::importElements(const std::vector<std::string> &filenames) {
    for (const auto &filename : filenames)
        m_textexport.importData(filename, m_storage);
}

void Parser::scanElements(const std::string &name) {
    m_console.showText("Input size of matrix: ");
    std::string input = Utilities::deleteSpaces(m_console.getInput());
    size_t numRows, numCols;
    char c;
    std::stringstream ss(input);
    // if we couldn't read numRows and numCols
    if (!(ss >> numRows >> numCols))
        throw ParserException("There should be only number of rows and number of columns\n");

    // if there is something else
    if (ss >> c)
        throw ParserException("There should be only number of rows and number of columns\n");

    std::vector <std::vector <double>> values(numRows, std::vector<double> (numCols, 0));

    for (size_t i = 0; i < numRows; ++i) {
        m_console.showText("Input " + std::to_string(i+1) + " row of matrix: ");

        auto row = Utilities::tokeniseInput(m_console.getInput());
        if (row.size() != numCols)
            throw ParserException("One row must have " + std::to_string(numCols) + " elements\n");

        for (size_t j = 0; j < numCols; ++j)
            values[i][j] = std::stod(row[j]);
    }
    auto matrix = Utilities::createMatrix(values);
    m_storage.addMatrix(name, matrix);
}

void Parser::printDet(const std::vector<std::string> &arguments) const {
    for (const auto &arg : arguments) {
        double det = m_storage.getMatrix(arg)->determinant();
        std::ostringstream ss;
        ss << "Determinant of matrix " << arg << " is " << det << + "\n";
        m_console.showText(ss.str());
    }
}

void Parser::printRank(const std::vector<std::string> &arguments) const {
    for (const auto &arg : arguments) {
        size_t rank = m_storage.getMatrix(arg)->rank();
        std::ostringstream ss;
        ss << "Rank of matrix " << arg << " is " << rank << "\n";
        m_console.showText(ss.str());
    }
}