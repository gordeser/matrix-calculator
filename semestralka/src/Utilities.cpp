
//
// Created by duama on 04.06.2023.
//

#include "Utilities.h"
#include "Commands.h"

#include <algorithm>


std::shared_ptr<Matrix> Utilities::createMatrix(const std::vector<std::vector<double>> &elements) const {
    size_t rows = elements.size();
    size_t cols = elements[0].size();
    bool isIdentity = true;

    // if numRows and numCols are equal and elements on diagonal are 1 and others are 0, then it is identity matrix
    if (rows == cols) {
        for (size_t i = 0; i < elements.size(); ++i)
            for (size_t j = 0; j < cols; ++j)
                if ((i != j and elements[i][j] != 0) or (i == j and elements[i][j] != 1)) {
                    isIdentity = false;
                    break;
                }
    } else
        isIdentity = false;

    if (isIdentity)
        return std::make_shared<IdentityMatrix>(rows, cols);

    size_t countZero = 0;
    // count zeros
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            if (elements[i][j] == 0) countZero++;

    // if there are more than 50% of zeros then make sparseMatrix else DenseMatrix
    if ((rows * cols)/2 < countZero) {
        std::map<std::pair<size_t, size_t>, double> sparseElements;
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                if (elements[i][j] != 0) {
                    auto pair = std::make_pair(i, j);
                    sparseElements[pair] = elements[i][j];
                }
        return std::make_shared<SparseMatrix>(rows, cols, sparseElements);
    }
    return std::make_shared<DenseMatrix>(rows, cols, elements);
}

std::vector<std::string> Utilities::tokeniseInput(const std::string &input) const {
    std::string modified = deleteSpaces(input);
    std::vector <std::string> result;
    std::istringstream iss(modified);
    std::string word;
    while (iss >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        result.push_back(word);
    }
    return result;
}

std::string Utilities::deleteSpaces(const std::string &str) const {
    std::string modified = str;

    // delete all spaces before all words
    size_t pos_start = modified.find_first_not_of(" \t\n\v\f\r");
    if (pos_start != std::string::npos)
        modified.erase(0, pos_start);

    // delete all spaces after all words
    size_t pos_end = modified.find_last_not_of(" \t\n\v\f\r");
    if (pos_end != std::string::npos)
        modified.erase(pos_end+1);

    // delete all "more than one" spaces between words in str
    size_t pos_between = modified.find("  ");
    while (pos_between != std::string::npos) {
        modified.replace(pos_between, 2, " ");
        pos_between = modified.find("  ");
    }

    return modified;
}

bool Utilities::checkName(const std::string &name) const {
    if (name.empty()) return false;

    std::string modified = name;
    std::transform(modified.begin(), modified.end(), modified.begin(), ::tolower);

    std::vector <std::string> reservedNames = {Commands::ADD, Commands::SUB, Commands::MUL, Commands::JOINRIGHT,
                                               Commands::JOINDOWN, Commands::TRIM, Commands::EXP, Commands::TRANS,
                                               Commands::INV, Commands::DET, Commands::RANK, Commands::GEM,
                                               Commands::SCAN, Commands::IMPORT, Commands::DEL, Commands::DELALL,
                                               Commands::EXPORT, Commands::EXPORTALL, Commands::PRINT, Commands::PRINTALL,
                                               Commands::HELP, Commands::EXIT, Commands::QUIT};

    // if name is one of reservedNames
    if (std::find(reservedNames.begin(), reservedNames.end(), modified) != reservedNames.end())
        return false;

    // if first symbol is digit
    if (std::isdigit(modified[0]))
        return false;

    for (char c : modified)
        if (!std::isalnum(c))
            return false;

    return true;
}