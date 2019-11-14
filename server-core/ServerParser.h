//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_SERVERPARSER_H
#define ISA_SERVERPARSER_H

#include "string"
#include "../common/Parser.h"

using namespace std;

/**
 * Parse server arguments
 */
class ServerParser : public Parser {
public:

    void printHelp() override;

    /**
     * Main method for parsing of arguments
     */
    void parseArgs() override;

    ServerParser(int argc, char **argv);

    ~ServerParser() = default;
};


#endif //ISA_SERVERPARSER_H
