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
        } else
            throw ParserException("Unknown command. Try \"help\"\n");
    } else {
        auto matrix = executeOperations(tokens);

        if (matrix != nullptr) {
            m_console.showText(matrix->print(""));
            return;
        } else
            throw ParserException("Unknown command. Try \"help\"\n");
    }
}


std::shared_ptr<Matrix> Parser::executeOperations(std::vector<std::string> &elements) {
    std::string operationName = elements[0];
    std::shared_ptr <Operation> operation;

    if (operationName == Commands::TRANS) {
        if (elements.size() < 2)
            throw ParserException("USAGE: trans <matrix>\n");

        auto operands = std::vector<std::string>(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> operand;

        if (operands.size() > 1) {
            operand = executeOperations(operands);
            if (operand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            operand = m_storage.getMatrix(operands[0]);

        operation = std::make_shared<TransposeOperation>(operand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::INV) {
        if (elements.size() < 2)
            throw ParserException("USAGE: inv <matrix>\n");

        auto operands = std::vector<std::string>(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> operand;

        if (operands.size() > 1) {
            operand = executeOperations(operands);
            if (operand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            operand = m_storage.getMatrix(operands[0]);

        operation = std::make_shared<InversionOperation>(operand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::GEM) {
        if (elements.size() < 2)
            throw ParserException("USAGE: gem <matrix>\n");

        auto operands = std::vector<std::string>(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> operand;

        if (operands.size() > 1) {
            operand = executeOperations(operands);
            if (operand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            operand = m_storage.getMatrix(operands[0]);

        operation = std::make_shared<GaussEliminationOperation>(operand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;


    } else if (operationName == Commands::ADD) {
        if (elements.size() < 3)
            throw ParserException("USAGE: add <matrix> <matrix>\n");

        auto firstOperand = m_storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1) {
            secondOperand = executeOperations(nextOperands);
            if (secondOperand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            secondOperand = m_storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<AdditionOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::SUB) {
        if (elements.size() < 3)
            throw ParserException("USAGE: sub <matrix> <matrix>\n");

        auto firstOperand = m_storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1) {
            secondOperand = executeOperations(nextOperands);
            if (secondOperand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            secondOperand = m_storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<SubtractionOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::MUL) {
        if (elements.size() < 3)
            throw ParserException("USAGE: mul <number> <matrix> OR mul <matrix> <matrix>\n");

        try {
            double numOperand = std::stod(elements[1]);
            auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
            std::shared_ptr <Matrix> matrixOperand;

            if (nextOperands.size() > 1) {
                matrixOperand = executeOperations(nextOperands);
                if (matrixOperand == nullptr)
                    throw ParserException("There is an error in nested operations\n");
            } else
                matrixOperand = m_storage.getMatrix(nextOperands[0]);

            operation = std::make_shared<MultiplicationNumberOperation>(matrixOperand, numOperand);
        } catch (std::invalid_argument &e) {
            auto firstOperand = m_storage.getMatrix(elements[1]);
            auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
            std::shared_ptr <Matrix> secondOperand;

            if (nextOperands.size() > 1) {
                secondOperand = executeOperations(nextOperands);
                if (secondOperand == nullptr)
                    throw ParserException("There is an error in nested operations\n");
            } else
                secondOperand = m_storage.getMatrix(nextOperands[0]);

            operation = std::make_shared<MultiplicationOperation>(firstOperand, secondOperand);
        } catch (std::out_of_range &e) {
            throw ParserException("Numbers are too large\n");
        }

        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::JOINRIGHT) {
        if (elements.size() < 3)
            throw ParserException("USAGE: joinright <matrix> <matrix>\n");

        auto firstOperand = m_storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1) {
            secondOperand = executeOperations(nextOperands);
            if (secondOperand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            secondOperand = m_storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<JoiningRightOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::JOINDOWN) {
        if (elements.size() < 3)
            throw ParserException("USAGE: joindown <matrix> <matrix>\n");

        auto firstOperand = m_storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1) {
            secondOperand = executeOperations(nextOperands);
            if (secondOperand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            secondOperand = m_storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<JoiningDownOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::TRIM) {
        if (elements.size() < 6)
            throw ParserException("USAGE: trim <matrix> <num_rows> <num_cols> <offset_rows> <offset_cols>\n");

        size_t numRows, numCols, offsetRows, offsetCols;
        try {
            numRows = std::stoull(elements[elements.size()-4]);
            numCols = std::stoull(elements[elements.size()-3]);
            offsetRows = std::stoull(elements[elements.size()-2]);
            offsetCols = std::stoull(elements[elements.size()-1]);
        } catch (std::invalid_argument &e) {
            throw ParserException("USAGE: trim <matrix> <num_rows> <num_cols> <offset_rows> <offset_cols>\n");
        } catch (std::out_of_range &e) {
            throw ParserException("Numbers are too large\n");
        }

        auto nextOperands = std::vector<std::string>(elements.begin()+1, elements.end()-4);
        std::shared_ptr <Matrix> matrixOperand;

        if (nextOperands.size() > 1) {
            matrixOperand = executeOperations(nextOperands);
            if (matrixOperand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            matrixOperand = m_storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<TrimmingOperation>(matrixOperand, numRows, numCols, offsetRows, offsetCols);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::EXP) {
        if (elements.size() < 3)
            throw ParserException("USAGE: exp <matrix> <number>\n");

        double numOperand;
        try {
            numOperand = std::stod(elements[elements.size()-1]);
        } catch (std::invalid_argument &e) {
            throw ParserException("USAGE: exp <matrix> <number>\n");
        } catch (std::out_of_range &e) {
            throw ParserException("Numbers are too large\n");
        }

        auto nextOperands = std::vector<std::string>(elements.begin()+1, elements.end()-1);
        std::shared_ptr<Matrix> matrixOperand;

        if (nextOperands.size() > 1) {
            matrixOperand = executeOperations(nextOperands);
            if (matrixOperand == nullptr)
                throw ParserException("There is an error in nested operations\n");
        } else
            matrixOperand = m_storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<ExponentiationOperation>(matrixOperand, numOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    }
    return nullptr;
}

void Parser::printHelp() {
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
