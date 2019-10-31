//
// Created by mabartos on 10/17/19.
//

#include "ServerParser.h"
#include <vector>
#include "../common/Errors.h"

void ServerParser::printHelp() {
    printf("PRINT HELP SERVER!\n");
}

ServerParser::ServerParser(int argc, char **argv) : Parser(argc, argv) {
    parseArgs();
}

void ServerParser::parseArgs() {
    if (this->argc == 1 || this->argc > 3)
        Errors::error(EXIT_FAILURE, "Wrong count of parameters!!");

    vector<string> vect;
    for (int i = 1; i < this->argc; i++) {
        string item(this->argv[i]);
        vect.push_back(item);
    }

    if (vect.size() == 1 && vect.at(0) == "-h") {
        printHelp();
    } else if (vect.size() == 2 && vect.at(0) == "-p") {
        this->serverPort = getValidPort(vect.at(1));
    } else {
        Errors::error(EXIT_FAILURE, "Invalid Parameters");
    }
}



