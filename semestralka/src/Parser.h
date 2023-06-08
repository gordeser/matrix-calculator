//
// Created by gordeser on 14.05.2023.
//

#ifndef PA2_PARSER_H
#define PA2_PARSER_H

#include "MatrixStorage.h"
#include "UserInterfaces/ConsoleUI.h"
#include "Utilities.h"
#include "Exports/TextExport.h"

class Parser {
    MatrixStorage m_storage;
    ConsoleUI m_console;
    Utilities m_utilities;
    TextExport m_textexport;

    std::shared_ptr<Matrix> executeOperations(std::vector <std::string> &operations);
    void printHelp();
    void printElements(const std::vector <std::string> &elements);
    void printAllElements();
    void exportElements(const std::string &filename, const std::vector <std::string> &elements);
    void exportAllElements(const std::string &filename);
    void deleteElements(const std::vector <std::string> &elements);
    void deleteAllElements();
    void importElements(const std::vector<std::string> &elements);
    void scanElements(const std::string &name);
    void printDet(const std::vector <std::string> &elements);
    void printRank(const std::vector <std::string> &elements);
public:
    void parseInput(std::string input);
};

#endif //PA2_PARSER_H
