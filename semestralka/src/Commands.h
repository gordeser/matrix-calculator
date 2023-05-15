//
// Created by gordeser on 15.05.2023.
//

#ifndef PA2_COMMANDS_H
#define PA2_COMMANDS_H

#include <string>

class Commands {
public:
    inline static const std::string ADD = "ADD";
    inline static const std::string SUB = "SUB";
    inline static const std::string MUL = "MUL";
    inline static const std::string JOINRIGHT = "JOINRIGHT";
    inline static const std::string JOINDOWN = "JOINDOWN";
    inline static const std::string TRIM = "TRIM";
    inline static const std::string EXP = "EXP";
    inline static const std::string TRANS = "TRANS";
    inline static const std::string INV = "INV";
    inline static const std::string DET = "DET";
    inline static const std::string RANK = "RANK";
    inline static const std::string GEM = "GEM";
    inline static const std::string SCAN = "SCAN";
    inline static const std::string IMPORT = "IMPORT";
    inline static const std::string DEL = "DEL";
    inline static const std::string DELALL = "DELALL";
    inline static const std::string EXPORT = "EXPORT";
    inline static const std::string EXPORTALL = "EXPORTALL";
    inline static const std::string PRINT = "PRINT";
    inline static const std::string PRINTALL = "PRINTALL";
    inline static const std::string HELP = "HELP";
    inline static const std::string EXIT = "EXIT";
};

#endif //PA2_COMMANDS_H
