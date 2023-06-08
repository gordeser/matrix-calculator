//
// Created by gordeser on 13.05.2023.
//

#ifndef PA2_TEXTEXPORT_H
#define PA2_TEXTEXPORT_H

#include "Export.h"
#include "../Utilities.h"

class TextExport : public Export {
    Utilities m_utilities;
public:
    void exportData(const std::string &filename, const std::vector <std::string> &names, const MatrixStorage &storage) override;
    void importData(const std::vector<std::string> &filenames, MatrixStorage &storage) override;
};

#endif //PA2_TEXTEXPORT_H
