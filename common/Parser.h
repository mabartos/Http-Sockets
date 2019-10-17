//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_PARSER_H
#define ISA_PARSER_H

#include "string"

using namespace std;

class Parser {
protected:
    int argc;
    char **argv;
    int serverPort = 0;

    int getValidPort(string const &port);

    bool isValidPort(string const &port);

    int isValidNumber(string const &port, int minNumber, int maxNumber);

public:
    Parser(int argc, char **argv);

    ~Parser() = default;

    virtual void printHelp() = 0;

    bool isPortSetUp();

    int getPort();

    virtual void parseArgs() = 0;
};


#endif //ISA_PARSER_H
