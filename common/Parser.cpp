//
// Created by mabartos on 10/17/19.
//

#include "Parser.h"
#include <vector>
#include "../common/Errors.h"

Parser::Parser(int argc, char **argv) : argc(argc), argv(argv) {}

int Parser::isValidNumber(string const &port, int minNumber, int maxNumber) {
    char *res;
    long number = strtol(port.c_str(), &res, 10);
    if (*res == 0) {
        // Boundaries for 'port'
        return (number >= minNumber && number <= maxNumber);
    }
    return false;
}

bool Parser::isValidPort(string const &port) {
    // Defined boundaries for port
    return isValidNumber(port, 1, 65535);
}

int Parser::getValidPort(string const &port) {
    if (isValidPort(port)) {
        return stoi(port);
    } else
        Errors::error(EXIT_FAILURE, "Invalid Port!");
    return EXIT_FAILURE;
}

bool Parser::isPortSetUp() {
    return this->serverPort != 0;
}

int Parser::getPort() {
    return this->serverPort;
}

bool Parser::isNumber(const string &item) {
    char *p;
    strtol(item.c_str(), &p, 10);
    return *p == 0;
}
