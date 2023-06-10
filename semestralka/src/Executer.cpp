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

std::shared_ptr<Matrix> Executer::executeOperations(std::vector<std::string> &elements, const MatrixStorage &storage) const {
    std::string operationName = elements[0];
    std::shared_ptr <Operation> operation;

    if (operationName == Commands::TRANS) {
        if (elements.size() < 2)
            throw ExecuterException("USAGE: trans <matrix>\n");

        auto operands = std::vector<std::string>(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> operand;

        if (operands.size() > 1)
            operand = executeOperations(operands, storage);
        else
            operand = storage.getMatrix(operands[0]);

        operation = std::make_shared<TransposeOperation>(operand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::INV) {
        if (elements.size() < 2)
            throw ExecuterException("USAGE: inv <matrix>\n");

        auto operands = std::vector<std::string>(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> operand;

        if (operands.size() > 1)
            operand = executeOperations(operands, storage);
        else
            operand = storage.getMatrix(operands[0]);

        operation = std::make_shared<InversionOperation>(operand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::GEM) {
        if (elements.size() < 2)
            throw ExecuterException("USAGE: gem <matrix>\n");

        auto operands = std::vector<std::string>(elements.begin()+1, elements.end());
        std::shared_ptr<Matrix> operand;

        if (operands.size() > 1)
            operand = executeOperations(operands, storage);
        else
            operand = storage.getMatrix(operands[0]);

        operation = std::make_shared<GaussEliminationOperation>(operand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;


    } else if (operationName == Commands::ADD) {
        if (elements.size() < 3)
            throw ExecuterException("USAGE: add <matrix> <matrix>\n");

        auto firstOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1)
            secondOperand = executeOperations(nextOperands, storage);
        else
            secondOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<AdditionOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::SUB) {
        if (elements.size() < 3)
            throw ExecuterException("USAGE: sub <matrix> <matrix>\n");

        auto firstOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1)
            secondOperand = executeOperations(nextOperands, storage);
        else
            secondOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<SubtractionOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::MUL) {
        if (elements.size() < 3)
            throw ExecuterException("USAGE: mul <number> <matrix> OR mul <matrix> <matrix>\n");

        try {
            double numOperand = std::stod(elements[1]);
            auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
            std::shared_ptr <Matrix> matrixOperand;

            if (nextOperands.size() > 1)
                matrixOperand = executeOperations(nextOperands, storage);
            else
                matrixOperand = storage.getMatrix(nextOperands[0]);

            operation = std::make_shared<MultiplicationNumberOperation>(matrixOperand, numOperand);
        } catch (std::invalid_argument &e) {
            auto firstOperand = storage.getMatrix(elements[1]);
            auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
            std::shared_ptr <Matrix> secondOperand;

            if (nextOperands.size() > 1)
                secondOperand = executeOperations(nextOperands, storage);
            else
                secondOperand = storage.getMatrix(nextOperands[0]);

            operation = std::make_shared<MultiplicationOperation>(firstOperand, secondOperand);
        } catch (std::out_of_range &e) {
            throw ExecuterException("Numbers are too large\n");
        }

        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::JOINRIGHT) {
        if (elements.size() < 3)
            throw ExecuterException("USAGE: joinright <matrix> <matrix>\n");

        auto firstOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1)
            secondOperand = executeOperations(nextOperands, storage);
        else
            secondOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<JoiningRightOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::JOINDOWN) {
        if (elements.size() < 3)
            throw ExecuterException("USAGE: joindown <matrix> <matrix>\n");

        auto firstOperand = storage.getMatrix(elements[1]);
        auto nextOperands = std::vector<std::string>(elements.begin()+2, elements.end());
        std::shared_ptr<Matrix> secondOperand;

        if (nextOperands.size() > 1)
            secondOperand = executeOperations(nextOperands, storage);
        else
            secondOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<JoiningDownOperation>(firstOperand, secondOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::TRIM) {
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

        if (nextOperands.size() > 1)
            matrixOperand = executeOperations(nextOperands, storage);
        else
            matrixOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<TrimmingOperation>(matrixOperand, numRows, numCols, offsetRows, offsetCols);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    } else if (operationName == Commands::EXP) {
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

        if (nextOperands.size() > 1) {
            matrixOperand = executeOperations(nextOperands, storage);
        } else
            matrixOperand = storage.getMatrix(nextOperands[0]);

        operation = std::make_shared<ExponentiationOperation>(matrixOperand, numOperand);
        auto result = m_utilities.createMatrix(operation->execute());
        return result;
    }
    throw ExecuterException("There is an error in operations\n");
}
