//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_SUBTRACTIONOPERATION_H
#define PA2_SUBTRACTIONOPERATION_H

#include <vector>
#include "BinaryOperation.h"

class SubtractionOperation  : public BinaryOperation {
public:
    std::vector <std::vector <double>> execute(const std::shared_ptr<Matrix> &a, const std::shared_ptr<Matrix> &b) override;
    std::vector <std::vector <double>> execute(const std::shared_ptr<Matrix> &a, double b) override;
};

#endif //PA2_SUBTRACTIONOPERATION_H
