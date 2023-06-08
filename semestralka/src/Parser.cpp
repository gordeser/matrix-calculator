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

void Parser::printRank(const std::vector<std::string> &elements) {
    for (const auto &elem : elements) {
        size_t rank = m_storage.getMatrix(elem)->rank();
        std::ostringstream ss;
        ss << "Rank of matrix " << elem << " is " << rank << "\n";
        m_console.showText(ss.str());
    }
}
