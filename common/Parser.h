//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_PARSER_H
#define ISA_PARSER_H

#include "string"

using namespace std;

/**
 * General Parser
 */
class Parser {
protected:
    int argc;
    char **argv;
    int serverPort = 0;

    /**
     * Check if port is valid and get the port
     * @param port
     * @return the valid port
     */
    int getValidPort(string const &port);

    /**
    *Check if port is valid
    * @param port
    * @return true, if port is valid
    */
    bool isValidPort(string const &port);

    /**
     * Helper function for validation of port
     * @param port
     * @param minNumber
     * @param maxNumber
     * @return
     */
    int isValidNumber(string const &port, int minNumber, int maxNumber);

public:
    Parser(int argc, char **argv);

    ~Parser() = default;

    virtual void printHelp() = 0;

    bool isPortSetUp();

    int getPort();

    virtual void parseArgs() = 0;

    /**
     *  Check if item is number
     * @param item
     * @return
     */
    static bool isNumber(string const &item);
};


#endif //ISA_PARSER_H
