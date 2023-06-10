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
    /** @var storage to save matrices */
    MatrixStorage m_storage;
    /** @var to work with console */
    ConsoleUI m_console;
    /** @var to use utilities */
    Utilities m_utilities;
    /** @var to export some text */
    TextExport m_textexport;

    /**
     * Method that execute given operations on matrices
     * @param operations that need to be executed
     * @return shared smart-pointer to the matrix after executed operations
     */
    std::shared_ptr<Matrix> executeOperations(std::vector <std::string> &operations) const;
    /** Method that prints help message */
    void printHelp() const;
    /**
     * Method that prints given elements
     * @param elements vector to print
     */
    void printElements(const std::vector <std::string> &elements) const;
    /** Method that prints all elements in database */
    void printAllElements() const;
    /**
     * Method that exports given elements into file
     * @param filename in that export elements
     * @param elements vector to export
     */
    void exportElements(const std::string &filename, const std::vector <std::string> &elements) const;
    /**
     * Method to export all elements in database into file
     * @param filename in that export elemnts
     */
    void exportAllElements(const std::string &filename) const;
    /**
     * Method that deletes given elements from database
     * @param elements to delete
     */
    void deleteElements(const std::vector <std::string> &elements);
    /**
     * Method that deletes all elements from database
     */
    void deleteAllElements();
    /**
     * Method that imports matrices from given filenames
     * @param filenames vector to import
     */
    void importElements(const std::vector<std::string> &filenames);
    /**
     * Method that scan elements of matrix with given name
     * @param name of matrix
     */
    void scanElements(const std::string &name);
    /**
     * Method that prints determinants of given matrices
     * @param elements vector to print their determinants
     */
    void printDet(const std::vector <std::string> &elements) const;
    /**
     * Method that prints ranks of given matrices
     * @param elements vector to print their ranks
     */
    void printRank(const std::vector <std::string> &elements) const;
public:
    /**
     * Method that parses user's input
     * @param input to parse
     */
    void parseInput(std::string input);
};

#endif //PA2_PARSER_H
