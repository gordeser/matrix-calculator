//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TEXTEXPORT_H
#define PA2_TEXTEXPORT_H

#include "Export.h"

class TextExport : public Export {
public:
    void exportData(const std::shared_ptr<Matrix> &matrix, const std::string &filename) override;
};

#endif //PA2_TEXTEXPORT_H
