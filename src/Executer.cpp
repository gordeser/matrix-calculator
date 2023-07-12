//
// Created by duama on 10.06.2023.
//

#include "Executer.h"
#include "Operations/Operation.h"
#include "Commands.h"
#include "Operations/ExponentiationOperation.h"
#include "Exceptions/ExecuterException.h"
#include "Operations/TransposeOperation.h"
#include "Operations/InversionOperation.h"
#include "Operations/GaussEliminationOperation.h"
#include "Operations/AdditionOperation.h"
#include "Operations/SubtractionOperation.h"
#include "Operations/MultiplicationNumberOperation.h"
#include "Operations/MultiplicationOperation.h"
#include "Operations/JoiningRightOperation.h"
#include "Operations/JoiningDownOperation.h"
#include "Operations/TrimmingOperation.h"

std::shared_ptr<Matrix> Executer::executeOperations(const std::vector<std::string> &elements, const MatrixStorage &storage) const {
    std::string operationName = elements[0];
    std::unique_ptr <Operation> operation;

    if (operationName == Commands::TRANS) {
        // if there is no arguments
        if (elements.size() < 2)
            throw ExecuterException("USAGE: trans <matrix>\n");

        std::vector<std::string> operands(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> matrixOperand;

        // if there are nested operations
        if (operands.size() > 1)
            matrixOperand = executeOperations(operands, storage);
        else
            matrixOperand = storage.getMatrix(operands[0]);

        operation = std::make_unique<TransposeOperation>(matrixOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::INV) {
        // if there is no arguments
        if (elements.size() < 2)
            throw ExecuterException("USAGE: inv <matrix>\n");

        std::vector<std::string> operands(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> matrixOperand;

        // if there are nested operations
        if (operands.size() > 1)
            matrixOperand = executeOperations(operands, storage);
        else
            matrixOperand = storage.getMatrix(operands[0]);

        operation = std::make_unique<InversionOperation>(matrixOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::GEM) {
        // if there is no arguments
        if (elements.size() < 2)
            throw ExecuterException("USAGE: gem <matrix>\n");

        std::vector<std::string> operands(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> matrixOperand;

        // if there are nested operations
        if (operands.size() > 1)
            matrixOperand = executeOperations(operands, storage);
        else
            matrixOperand = storage.getMatrix(operands[0]);

        operation = std::make_unique<GaussEliminationOperation>(matrixOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::ADD) {
        // if there are less than 2 arguments
        if (elements.size() < 3)
            throw ExecuterException("USAGE: add <matrix> <matrix>\n");

        auto firstMatrixOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondMatrixOperand;

        // if there are nested operations
        if (nextOperands.size() > 1)
            secondMatrixOperand = executeOperations(nextOperands, storage);
        else
            secondMatrixOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_unique<AdditionOperation>(firstMatrixOperand, secondMatrixOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::SUB) {
        // if there are less than 2 arguments
        if (elements.size() < 3)
            throw ExecuterException("USAGE: sub <matrix> <matrix>\n");

        auto firstMatrixOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondMatrixOperand;

        if (nextOperands.size() > 1)
            secondMatrixOperand = executeOperations(nextOperands, storage);
        else
            secondMatrixOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_unique<SubtractionOperation>(firstMatrixOperand, secondMatrixOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::MUL) {
        // if there are less than 2 arguments
        if (elements.size() < 3)
            throw ExecuterException("USAGE: mul <number> <matrix> OR mul <matrix> <matrix>\n");

        try {
            double numOperand = std::stod(elements[1]);
            auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
            std::shared_ptr <Matrix> matrixOperand;

            // if there are nested operations
            if (nextOperands.size() > 1)
                matrixOperand = executeOperations(nextOperands, storage);
            else
                matrixOperand = storage.getMatrix(nextOperands[0]);

            operation = std::make_unique<MultiplicationNumberOperation>(matrixOperand, numOperand);
        } catch (std::invalid_argument &e) {
            auto firstMatrixOperand = storage.getMatrix(elements[1]);
            auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
            std::shared_ptr <Matrix> secondMatrixOperand;

            // if there are nested operations
            if (nextOperands.size() > 1)
                secondMatrixOperand = executeOperations(nextOperands, storage);
            else
                secondMatrixOperand = storage.getMatrix(nextOperands[0]);

            operation = std::make_unique<MultiplicationOperation>(firstMatrixOperand, secondMatrixOperand);
        } catch (std::out_of_range &e) {
            throw ExecuterException("Numbers are too large\n");
        }

        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::JOINRIGHT) {
        // if there are less than 2 arguments
        if (elements.size() < 3)
            throw ExecuterException("USAGE: joinright <matrix> <matrix>\n");

        auto firstOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        // if there are nested operations
        if (nextOperands.size() > 1)
            secondOperand = executeOperations(nextOperands, storage);
        else
            secondOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_unique<JoiningRightOperation>(firstOperand, secondOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::JOINDOWN) {
        // if there are less than 2 arguments
        if (elements.size() < 3)
            throw ExecuterException("USAGE: joindown <matrix> <matrix>\n");

        auto firstOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        // if there are nested operations
        if (nextOperands.size() > 1)
            secondOperand = executeOperations(nextOperands, storage);
        else
            secondOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_unique<JoiningDownOperation>(firstOperand, secondOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::TRIM) {
        // if there are less than 6 arguments
        if (elements.size() < 6)
            throw ExecuterException("USAGE: trim <matrix> <num_rows> <num_cols> <offset_rows> <offset_cols>\n");

        size_t numRows, numCols, offsetRows, offsetCols;
        try {
            numRows = std::stoull(elements[elements.size()-4]);
            numCols = std::stoull(elements[elements.size()-3]);
            offsetRows = std::stoull(elements[elements.size()-2]);
            offsetCols = std::stoull(elements[elements.size()-1]);
        } catch (std::invalid_argument &e) {
            throw ExecuterException("USAGE: trim <matrix> <num_rows> <num_cols> <offset_rows> <offset_cols>\n");
        } catch (std::out_of_range &e) {
            throw ExecuterException("Numbers are too large\n");
        }

        auto nextOperands = std::vector<std::string>(elements.begin()+1, elements.end()-4);
        std::shared_ptr <Matrix> matrixOperand;

        // if there are nested operations
        if (nextOperands.size() > 1)
            matrixOperand = executeOperations(nextOperands, storage);
        else
            matrixOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_unique<TrimmingOperation>(matrixOperand, numRows, numCols, offsetRows, offsetCols);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::EXP) {
        // if there are less than 2 arguments
        if (elements.size() < 3)
            throw ExecuterException("USAGE: exp <matrix> <number>\n");

        double numOperand;
        try {
            numOperand = std::stod(elements[elements.size()-1]);
        } catch (std::invalid_argument &e) {
            throw ExecuterException("USAGE: exp <matrix> <number>\n");
        } catch (std::out_of_range &e) {
            throw ExecuterException("Numbers are too large\n");
        }

        auto nextOperands = std::vector<std::string>(elements.begin()+1, elements.end()-1);
        std::shared_ptr<Matrix> matrixOperand;

        // if there are nested operations
        if (nextOperands.size() > 1) {
            matrixOperand = executeOperations(nextOperands, storage);
        } else
            matrixOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_unique<ExponentiationOperation>(matrixOperand, numOperand);
        auto result = Utilities::createMatrix(operation->execute());
        return result;
    }
    throw ExecuterException("Unknown operation. Try input \"HELP\"\n");
}
