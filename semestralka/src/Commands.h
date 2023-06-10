//
// Created by gordeser on 15.05.2023.
//

#ifndef PA2_COMMANDS_H
#define PA2_COMMANDS_H

#include <string>

class Commands {
public:
    inline static const std::string ADD = "add";
    inline static const std::string SUB = "sub";
    inline static const std::string MUL = "mul";
    inline static const std::string JOINRIGHT = "joinright";
    inline static const std::string JOINDOWN = "joindown";
    inline static const std::string TRIM = "trim";
    inline static const std::string EXP = "exp";
    inline static const std::string TRANS = "trans";
    inline static const std::string INV = "inv";
    inline static const std::string DET = "det";
    inline static const std::string RANK = "rank";
    inline static const std::string GEM = "gem";
    inline static const std::string SCAN = "scan";
    inline static const std::string IMPORT = "import";
    inline static const std::string DEL = "del";
    inline static const std::string DELALL = "delall";
    inline static const std::string EXPORT = "export";
    inline static const std::string EXPORTALL = "exportall";
    inline static const std::string PRINT = "print";
    inline static const std::string PRINTALL = "printall";
    inline static const std::string HELP = "help";
    inline static const std::string EXIT = "exit";
    inline static const std::string QUIT = "quit";
};

#endif //PA2_COMMANDS_H
